<?php

/**
 * @file
 * Theme settings
 */

$path_to_enso_light = drupal_get_path('theme', 'enso_light');
require_once($path_to_enso_light . '/inc/enso_light_selector_style.inc');

/**
 * Implimentation of hook_form_system_theme_settings_alter()
 *
 * @param $form: Nested array of form elements that comprise the form.
 * @param $form_state: A keyed array containing the current state of the form.
 */
function enso_light_form_system_theme_settings_alter(&$form, &$form_state)  {
  $form['enso'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ensō Custom Settings'),
    '#weight' => -15,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['enso']['css_selectors'] = array(
    '#type' => 'textarea',
    '#cols' => '120',
    '#rows' => '5',
    '#resizable' => TRUE,
    '#title' => t('CSS Selectors'),
    '#default_value' => theme_get_setting('css_selectors'),
    '#description' => t('Enter a list of CSS selectors, each group on a new line <em>e.g. #header, .footer etc</em>. For each selector specified here, further styling options will be displayed below after saving.'),
  );

  // Dynamically generate sets of form elements based on user-defined CSS selectors
  $css_selector_lines = explode("\n", theme_get_setting('css_selectors'));
  foreach ($css_selector_lines as $css_selector_line) {
    $css_selector_pair = explode('|', $css_selector_line);
    $css_selector = trim($css_selector_pair[0]);
    $css_selector_name = trim($css_selector_pair[1]);
    $name = preg_replace('/[^a-z0-9]+/', '_', strtolower($css_selector_name));
    $form['enso'][$name] = enso_light_selector_form($css_selector, $css_selector_name);
  }

  // Attach custom submit handler to the form
  $form['#submit'][] = 'enso_light_settings_submit';

}

function enso_light_settings_submit(&$form, &$form_state)  {

  // Save background images and generate CSS
  $css = '';
  $css_selector_lines = explode("\n", theme_get_setting('css_selectors'));
  foreach ($css_selector_lines as $css_selector_line) {
    $css_selector_pair = explode("|", $css_selector_line);
    $css_selector = trim($css_selector_pair[0]);
    $css_selector_name = trim($css_selector_pair[1]);
    enso_light_selector_bg_save($form, $form_state, $css_selector_name);
    $css .= enso_light_selector_generate_css($form_state, $css_selector, $css_selector_name);
  }

  // Save custom CSS to file
  $path = 'public://adaptivetheme/enso_light_files';
  file_prepare_directory($path, FILE_CREATE_DIRECTORY);
  $file_name = 'enso_light.dynamic.css';
  $filepath = $path . '/' . $file_name;
  file_unmanaged_save_data($css, $filepath, FILE_EXISTS_REPLACE);

}
