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
  $form['enso']['your_option'] = array(
    '#type' => 'checkbox',
    '#title' => t('Your Options'),
    '#default_value' => theme_get_setting('your_option'),
  );
  $form['enso']['css_selectors'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS Classes and IDs'),
    '#default_value' => theme_get_setting('css_selectors'),
    '#description' => t('Enter a list of CSS classes and IDs, separated by commas <em>e.g. #header .footer etc</em>. For each class and ID specified here, further styling options will be displayed below after saving.'),
  );

  // Dynamically generate sets of form elements based on specified CSS classes and ids
  $css_selectors = explode(',', preg_replace('/\s+/', '', theme_get_setting('css_selectors')));
  foreach ($css_selectors as $css_selector) {
    $css_selector_prefixes = array('.', '#');
    $name = str_replace($css_selector_prefixes, '', $css_selector);
    $form['enso'][$name] = enso_light_selector_form($name, $css_selector);
  }

  // Attach custom submit handler to the form
  $form['#submit'][] = 'enso_light_settings_submit';

}

function enso_light_settings_submit(&$form, &$form_state)  {

  // Save background images and generate CSS
  $css = '';
  $css_selectors = explode(',', preg_replace('/\s+/', '', theme_get_setting('css_selectors')));
  foreach ($css_selectors as $css_selector) {
    $css_selector_prefixes = array('.', '#');
    $name = str_replace($css_selector_prefixes, '', $css_selector);
    enso_light_selector_bg_save($form, $form_state, $name);
    $css .= enso_light_selector_generate_css($form_state, $name, $css_selector);
  }

  // Save custom CSS to file
  $path = 'public://adaptivetheme/enso_light_files';
  file_prepare_directory($path, FILE_CREATE_DIRECTORY);
  $file_name = 'enso_light.dynamic.css';
  $filepath = $path . '/' . $file_name;
  file_unmanaged_save_data($css, $filepath, FILE_EXISTS_REPLACE);

}
