<?php

/**
 * @file
 * Functions to build subforms, save background image and generate CSS for a custom CSS selector
 */


/**
 * Build the subform for a custom CSS selector
 */
function enso_light_selector_form($name) {

  $form = array();

  $form[$name . '_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t(ucfirst($name)),
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
  );
  // Background color
  $form[$name . '_fieldset'][$name . '_bg_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Background color'),
    '#default_value' => theme_get_setting($name . '_bg_color'),
    '#description' => t('Enter a valid CSS color value <em>e.g. red can be defined as #f00, #ff0000, rgb(255,0,0), rgba(255,0,0,0.0) or simply red. Write transparent for no color.</em>'),
  );
  // Use background image checkbox
  $form[$name . '_fieldset'][$name . '_use_bg_image'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use background image'),
    '#default_value' => theme_get_setting($name . '_use_bg_image'),
    '#tree' => FALSE,
  );
  // Background image options fieldset
  $form[$name . '_fieldset'][$name . '_bg'] = array(
    '#type' => 'fieldset',
    '#title' => t('Background image options'),
    '#states' => array(
      // Hide background image options by default
      'invisible' => array(
        'input[name="' . $name . '_use_bg_image"]' => array('checked' => FALSE),
      ),
    ),
  );

  // Default path for background image
  $bg_path = theme_get_setting($name . '_bg_path');
  if (file_uri_scheme($bg_path) == 'public') {
    $bg_path = file_uri_target($bg_path);
  }
  // Background image file name (disabled to prevent data entry)
  $form[$name . '_fieldset'][$name . '_bg'][$name . '_bg_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to background image'),
    '#default_value' => $bg_path,
    '#disabled' => TRUE,
  );
  // Background image upload field
  $form[$name . '_fieldset'][$name . '_bg'][$name . '_bg_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload background image'),
    '#description' => t('Upload a new image for the background.'),
  );
  // Background position
  $form[$name . '_fieldset'][$name . '_bg'][$name . '_bg_position'] = array(
    '#type' => 'select',
    '#title' => t('Background position'),
    '#options' => array(
      'left top' => t('Left top'),
      'left center' => t('Left center'),
      'left bottom' => t('Left bottom'),
      'right top' => t('Right top'),
      'right center' => t('Right center'),
      'right bottom' => t('Right bottom'),
      'center top' => t('Center top'),
      'center center' => t('Center center'),
      'center bottom' => t('Center bottom'),
    ),
    '#default_value' => theme_get_setting($name . '_bg_position'),
  );
  // Background repeat
  $form[$name . '_fieldset'][$name . '_bg'][$name . '_bg_repeat'] = array(
    '#type' => 'select',
    '#title' => t('Background repeat'),
    '#options' => array(
      'repeat' => t('Repeat horizontally and vertically'),
      'repeat-x' => t('Repeat horizontally only'),
      'repeat-y' => t('Repeat vertically only'),
      'no-repeat' => t('Don\'t repeat'),
      'inherit'=> t('Inherit'),
    ),
    '#default_value' => theme_get_setting($name . '_bg_repeat'),
  );
  // Background attachment
  $form[$name . '_fieldset'][$name . '_bg'][$name . '_bg_attachment'] = array(
    '#type' => 'select',
    '#title' => t('Background attachment'),
    '#options' => array(
      'scroll' => t('Scroll'),
      'fixed' => t('Fixed'),
      'local' => t('Local'),
    ),
    '#default_value' => theme_get_setting($name . '_bg_attachment'),
  );
  // Override foreground colors checkbox
  $form[$name . '_fieldset'][$name . '_override_fg_colors'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override foreground colors'),
    '#default_value' => theme_get_setting($name . '_override_fg_colors'),
    '#tree' => FALSE,
  );
  // Foreground colors fieldset
  $form[$name . '_fieldset'][$name . '_fg'] = array(
    '#type' => 'fieldset',
    '#title' => t('Foreground colors'),
    '#states' => array(
      // Hide foreground colors fieldset by default
      'invisible' => array(
        'input[name="' . $name . '_override_fg_colors"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Color
  $form[$name . '_fieldset'][$name . '_fg'][$name . '_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Color'),
    '#default_value' => theme_get_setting($name . '_color'),
  );
  // Link color
  $form[$name . '_fieldset'][$name . '_fg'][$name . '_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link color'),
    '#default_value' => theme_get_setting($name . '_link_color'),
  );
  // Link decoration
  $form[$name . '_fieldset'][$name . '_fg'][$name . '_link_decoration'] = array(
    '#type' => 'select',
    '#title' => t('Link decoration'),
    '#options' => array(
      'none' => t('None'),
      'underline' => t('Underline'),
      'overline' => t('Overline'),
      'line-through' => t('Line-through'),
      'inherit' => t('Inherit'),
    ),
    '#default_value' => theme_get_setting($name . '_link_decoration'),
  );
  // Link hover and focus color
  $form[$name . '_fieldset'][$name . '_fg'][$name . '_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link hover and focus color'),
    '#default_value' => theme_get_setting($name . '_hover_color'),
    //'#description' => t('Enter a valid CSS color value <em>e.g. red can be defined as #f00, #ff0000, rgb(255,0,0), rgba(255,0,0,0.0) or simply red. Write transparent for no color.</em>'),
  );
  // Link hover and focus decoration
  $form[$name . '_fieldset'][$name . '_fg'][$name . '_hover_decoration'] = array(
    '#type' => 'select',
    '#title' => t('Link hover and focus decoration'),
    '#options' => array(
      'none' => t('None'),
      'underline' => t('Underline'),
      'overline' => t('Overline'),
      'line-through' => t('Line-through'),
      'inherit' => t('Inherit'),
    ),
    '#default_value' => theme_get_setting($name . '_hover_decoration'),
  );

  return $form;
}

/**
 * Save the background image for a custom CSS selector
 */
function enso_light_selector_bg_save(&$form, &$form_state, $name) {
  // Get the previous value
  $previous = 'public://' . $form['enso'][$name][$name . '_fieldset'][$name . '_bg'][$name . '_bg_path']['#default_value'];
  $file = file_save_upload($name . '_bg_upload');
  if ($file) {
    $parts = pathinfo($file->filename);
    $destination = 'public://' . $parts['basename'];
    $file->status = FILE_STATUS_PERMANENT;
    if(file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
      $_POST[$name . '_bg_path'] = $form_state['values'][$name . '_bg_path'] = $destination;
      // If new file has a different name than the old one, delete the old
      if ($destination != $previous) {
        // drupal_unlink($previous);
      }
    }
  } else {
    // Avoid error when the form is submitted without specifying a new image
    $_POST[$name . '_bg_path'] = $form_state['values'][$name . '_bg_path'] = $previous;
  }

}

/**
 * Generate the CSS for a custom CSS selector
 */
function enso_light_selector_generate_css(&$form_state, $name, $css_selector) {

  $css = '';
  
  // Generate background
  $css .= $css_selector . ' { ';
  $bg_color = $form_state['values'][$name . '_bg_color'];
  $bg_color = $bg_color == '' ? 'transparent' : $bg_color;
  if ($form_state['values'][$name . '_use_bg_image'])  {

    $bg_url = 'url(\'' . file_create_url($form_state['values'][$name . '_bg_path']) . '\') ';
    $bg_position = $form_state['values'][$name . '_bg_position'] . ' ';
    $bg_attachment = $form_state['values'][$name . '_bg_attachment'] . ' ';
    $bg_repeat = $form_state['values'][$name . '_bg_repeat'] . ' ';

    $css .= 'background: ' . $bg_url . $bg_position . $bg_attachment . $bg_repeat . $bg_color . ';';
  }
  else {
    $css .= 'background-color: ' . $bg_color . ';';
  }
  $css .= ' }' . "\n";

  // Generate foreground color
  if ($form_state['values'][$name . '_override_fg_colors'])  {
    // Color
    $css .= $css_selector . ' { ';
    $color = $form_state['values'][$name . '_color'];
    $color = $color == '' ? 'inherit' : $color;
    $css .= 'color: ' . $color . ';';
    $css .= ' }' . "\n";
  }

  // Generate foreground link colors
  if ($form_state['values'][$name . '_override_fg_colors'])  {
    // Link color & decoration
    $css .= $css_selector . ' a { ';
    $link_color = $form_state['values'][$name . '_link_color'];
    $link_color = $link_color == '' ? 'inherit' : $link_color;
    $css .= 'color: ' . $link_color . '; ';
    $link_decoration = $form_state['values'][$name . '_link_decoration'];
    $css .= 'text-decoration: ' . $link_decoration . ';';
    $css .= ' }' . "\n";

    // Link hover and focus color
    $css .= $css_selector . ' a:hover, ' . $css_selector . ' a:focus { ';
    $hover_color = $form_state['values'][$name . '_hover_color'];
    $hover_color = $hover_color == '' ? 'inherit' : $hover_color;
    $css .= 'color: ' . $hover_color . '; ';
    $hover_decoration = $form_state['values'][$name . '_hover_decoration'];
    $css .= 'text-decoration: ' . $hover_decoration . ';';
    $css .= ' }' . "\n";
  }

  return $css;
}
