<?php

/**
 * @file
 * Functions to build subforms, save background image and generate CSS for a custom CSS selector
 */


/**
 * Build the subform for a custom CSS selector
 */
function enso_light_selector_form($name, $css_selector) {

  $form = array();

  $form[$name . '_fieldset'] = array(
    '#type' => 'fieldset',
    //'#title' => t(ucfirst(str_replace(array('-', '_'), ' ', $name))),
    '#title' => t('Styling for selector "' . $css_selector . '"'),
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
  );
  // Use layout checkbox
  $form[$name . '_fieldset'][$name . '_use_layout'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use layout'),
    '#default_value' => theme_get_setting($name . '_use_layout'),
    '#tree' => FALSE,
  );
  // Layout options fieldset
  $form[$name . '_fieldset'][$name . '_layout_opts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout options'),
    '#states' => array(
      // Hide layout options by default
      'invisible' => array(
        'input[name="' . $name . '_use_layout"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Width
  $form[$name . '_fieldset'][$name . '_layout_opts'][$name . '_layout_width'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Width'),
    '#default_value' => theme_get_setting($name . '_layout_width'),
  );
  // Height
  $form[$name . '_fieldset'][$name . '_layout_opts'][$name . '_layout_height'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Height'),
    '#default_value' => theme_get_setting($name . '_layout_height'),
  );
  // Margins
  $form[$name . '_fieldset'][$name . '_layout_opts'][$name . '_layout_margins'] = array(
    '#type' => 'textfield',
    '#size' => '10',
    '#title' => t('Margins'),
    '#default_value' => theme_get_setting($name . '_layout_margins'),
  );
  // Padding
  $form[$name . '_fieldset'][$name . '_layout_opts'][$name . '_layout_padding'] = array(
    '#type' => 'textfield',
    '#size' => '10',
    '#title' => t('Padding'),
    '#default_value' => theme_get_setting($name . '_layout_padding'),
  );
  // Use background colors checkbox
  $form[$name . '_fieldset'][$name . '_use_bg_colors'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use background color'),
    '#default_value' => theme_get_setting($name . '_use_bg_colors'),
    '#tree' => FALSE,
  );
  // Background color options fieldset
  $form[$name . '_fieldset'][$name . '_bg_color_opts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Background color options'),
    '#states' => array(
      // Hide background colors by default
      'invisible' => array(
        'input[name="' . $name . '_use_bg_colors"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Background color(s)
  $form[$name . '_fieldset'][$name . '_bg_color_opts'][$name . '_bg_color'] = array(
    '#type' => 'textfield',
    '#size' => '120',
    '#title' => t('Background color(s)'),
    '#default_value' => theme_get_setting($name . '_bg_color'),
    '#description' => t('Enter a valid CSS color value <em>e.g. red can be defined as #f00, #ff0000, rgb(255,0,0), rgba(255,0,0,0.0) or simply red. Write transparent for no color.</em>'),
  );
  // Background gradient direction
  $form[$name . '_fieldset'][$name . '_bg_color_opts'][$name . '_bg_gradient'] = array(
    '#type' => 'select',
    '#title' => t('Background gradient'),
    '#options' => array(
      'none' => t('None'),
      'top-to-bottom' => t('Linear: Top to bottom'),
      'left-to-right' => t('Linear: Left to right'),
    ),
    '#default_value' => theme_get_setting($name . '_bg_gradient'),
  );
  // Use background image checkbox
  $form[$name . '_fieldset'][$name . '_use_bg_image'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use background image'),
    '#default_value' => theme_get_setting($name . '_use_bg_image'),
    '#tree' => FALSE,
  );
  // Background image options fieldset
  $form[$name . '_fieldset'][$name . '_bg_image_opts'] = array(
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
  $form[$name . '_fieldset'][$name . '_bg_image_opts'][$name . '_bg_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to background image'),
    '#default_value' => $bg_path,
    '#disabled' => TRUE,
  );
  // Background image upload field
  $form[$name . '_fieldset'][$name . '_bg_image_opts'][$name . '_bg_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload background image'),
    '#description' => t('Upload a new image for the background.'),
  );
  // Background position
  $form[$name . '_fieldset'][$name . '_bg_image_opts'][$name . '_bg_position'] = array(
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
  $form[$name . '_fieldset'][$name . '_bg_image_opts'][$name . '_bg_repeat'] = array(
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
  $form[$name . '_fieldset'][$name . '_bg_image_opts'][$name . '_bg_attachment'] = array(
    '#type' => 'select',
    '#title' => t('Background attachment'),
    '#options' => array(
      'scroll' => t('Scroll'),
      'fixed' => t('Fixed'),
      'local' => t('Local'),
    ),
    '#default_value' => theme_get_setting($name . '_bg_attachment'),
  );
  // Use foreground colors checkbox
  $form[$name . '_fieldset'][$name . '_use_fg'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use foreground colors and decoration'),
    '#default_value' => theme_get_setting($name . '_use_fg'),
    '#tree' => FALSE,
  );
  // Foreground options fieldset
  $form[$name . '_fieldset'][$name . '_fg_opts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Foreground options'),
    '#states' => array(
      // Hide foreground colors fieldset by default
      'invisible' => array(
        'input[name="' . $name . '_use_fg"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Color
  $form[$name . '_fieldset'][$name . '_fg_opts'][$name . '_color'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#title' => t('Color'),
    '#default_value' => theme_get_setting($name . '_color'),
  );
  // Link color
  $form[$name . '_fieldset'][$name . '_fg_opts'][$name . '_link_color'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#title' => t('Link color'),
    '#default_value' => theme_get_setting($name . '_link_color'),
  );
  // Link decoration
  $form[$name . '_fieldset'][$name . '_fg_opts'][$name . '_link_decoration'] = array(
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
  $form[$name . '_fieldset'][$name . '_fg_opts'][$name . '_hover_color'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#title' => t('Link hover and focus color'),
    '#default_value' => theme_get_setting($name . '_hover_color'),
    //'#description' => t('Enter a valid CSS color value <em>e.g. red can be defined as #f00, #ff0000, rgb(255,0,0), rgba(255,0,0,0.0) or simply red. Write transparent for no color.</em>'),
  );
  // Link hover and focus decoration
  $form[$name . '_fieldset'][$name . '_fg_opts'][$name . '_hover_decoration'] = array(
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
  // Use borders checkbox
  $form[$name . '_fieldset'][$name . '_use_borders'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use borders'),
    '#default_value' => theme_get_setting($name . '_use_borders'),
    '#tree' => FALSE,
  );
  // Border options fieldset
  $form[$name . '_fieldset'][$name . '_border_opts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Border options'),
    '#states' => array(
      // Hide borders fieldset by default
      'invisible' => array(
        'input[name="' . $name . '_use_borders"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Border color
  $form[$name . '_fieldset'][$name . '_border_opts'][$name . '_border_color'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#title' => t('Border color'),
    '#default_value' => theme_get_setting($name . '_border_color'),
  );
  // Border width
  $form[$name . '_fieldset'][$name . '_border_opts'][$name . '_border_width'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Border width'),
    '#default_value' => theme_get_setting($name . '_border_width'),
  );
  // Border style
  $form[$name . '_fieldset'][$name . '_border_opts'][$name . '_border_style'] = array(
    '#type' => 'select',
    '#title' => t('Border style'),
    '#options' => array(
      'none' => t('None'),
      'dotted' => t('Dotted'),
      'dashed' => t('Dashed'),
      'solid' => t('Solid'),
      'double' => t('Double'),
      'groove' => t('Groove'),
      'ridge' => t('Ridge'),
      'inset' => t('Inset'),
      'outset' => t('Outset'),
    ),
    '#default_value' => theme_get_setting($name . '_border_style'),
  );
  // Borders container
  $form[$name . '_fieldset'][$name . '_border_opts'][$name . '_borders_container'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Apply borders to</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  // Borders top
  $form[$name . '_fieldset'][$name . '_border_opts'][$name . '_borders_container'][$name . '_border_top'] = array(
    '#type' => 'checkbox',
    '#title' => t('Top'),
    '#default_value' => theme_get_setting($name . '_border_top'),
  );
  // Borders right
  $form[$name . '_fieldset'][$name . '_border_opts'][$name . '_borders_container'][$name . '_border_right'] = array(
    '#type' => 'checkbox',
    '#title' => t('Right'),
    '#default_value' => theme_get_setting($name . '_border_right'),
  );
  // Borders bottom
  $form[$name . '_fieldset'][$name . '_border_opts'][$name . '_borders_container'][$name . '_border_bottom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bottom'),
    '#default_value' => theme_get_setting($name . '_border_bottom'),
  );
  // Borders left
  $form[$name . '_fieldset'][$name . '_border_opts'][$name . '_borders_container'][$name . '_border_left'] = array(
    '#type' => 'checkbox',
    '#title' => t('Left'),
    '#default_value' => theme_get_setting($name . '_border_left'),
  );
  // Use rounded corners checkbox
  $form[$name . '_fieldset'][$name . '_use_radius'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use rounded corners'),
    '#default_value' => theme_get_setting($name . '_use_radius'),
    '#tree' => FALSE,
  );
  // Rounded corner options fieldset
  $form[$name . '_fieldset'][$name . '_radius_opts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Rounded corner options'),
    '#states' => array(
      // Hide radius fieldset by default
      'invisible' => array(
        'input[name="' . $name . '_use_radius"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Rounded corner radius
  $form[$name . '_fieldset'][$name . '_radius_opts'][$name . '_radius'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Rounded corner radius'),
    '#default_value' => theme_get_setting($name . '_radius'),
  );
  // Rounded corners container
  $form[$name . '_fieldset'][$name . '_radius_opts'][$name . '_radius_container'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Apply rounded corners to</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  // Rounded corner radius top-left
  $form[$name . '_fieldset'][$name . '_radius_opts'][$name . '_radius_container'][$name . '_top_left_radius'] = array(
    '#type' => 'checkbox',
    '#title' => t('Top-left'),
    '#default_value' => theme_get_setting($name . '_top_left_radius'),
  );
  // Rounded corner radius top-right
  $form[$name . '_fieldset'][$name . '_radius_opts'][$name . '_radius_container'][$name . '_top_right_radius'] = array(
    '#type' => 'checkbox',
    '#title' => t('Top-right'),
    '#default_value' => theme_get_setting($name . '_top_right_radius'),
  );
  // Rounded corner radius bottom-right
  $form[$name . '_fieldset'][$name . '_radius_opts'][$name . '_radius_container'][$name . '_bottom_right_radius'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bottom-right'),
    '#default_value' => theme_get_setting($name . '_bottom_right_radius'),
  );
  // Rounded corner radius bottom-left
  $form[$name . '_fieldset'][$name . '_radius_opts'][$name . '_radius_container'][$name . '_bottom_left_radius'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bottom-left'),
    '#default_value' => theme_get_setting($name . '_bottom_left_radius'),
  );
  // Use box shadow checkbox
  $form[$name . '_fieldset'][$name . '_use_box_shadow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use box shadow'),
    '#default_value' => theme_get_setting($name . '_use_box_shadow'),
    '#tree' => FALSE,
  );
  // Box shadow options fieldset
  $form[$name . '_fieldset'][$name . '_box_shadow_opts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Box shadow options'),
    '#states' => array(
      // Hide box shadow fieldset by default
      'invisible' => array(
        'input[name="' . $name . '_use_box_shadow"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Box shadow distance
  $form[$name . '_fieldset'][$name . '_box_shadow_opts'][$name . '_box_shadow_distance'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Distance'),
    '#default_value' => theme_get_setting($name . '_box_shadow_distance'),
  );
  // Box shadow blur
  $form[$name . '_fieldset'][$name . '_box_shadow_opts'][$name . '_box_shadow_blur'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Blur'),
    '#default_value' => theme_get_setting($name . '_box_shadow_blur'),
  );
  // Box shadow color
  $form[$name . '_fieldset'][$name . '_box_shadow_opts'][$name . '_box_shadow_color'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#title' => t('Color'),
    '#default_value' => theme_get_setting($name . '_box_shadow_color'),
  );
  // Use text shadow checkbox
  $form[$name . '_fieldset'][$name . '_use_text_shadow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use text shadow'),
    '#default_value' => theme_get_setting($name . '_use_text_shadow'),
    '#tree' => FALSE,
  );
  // Text shadow options fieldset
  $form[$name . '_fieldset'][$name . '_text_shadow_opts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Text shadow options'),
    '#states' => array(
      // Hide text shadow fieldset by default
      'invisible' => array(
        'input[name="' . $name . '_use_text_shadow"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Text shadow distance
  $form[$name . '_fieldset'][$name . '_text_shadow_opts'][$name . '_text_shadow_distance'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Distance'),
    '#default_value' => theme_get_setting($name . '_text_shadow_distance'),
  );
  // Text shadow blur
  $form[$name . '_fieldset'][$name . '_text_shadow_opts'][$name . '_text_shadow_blur'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Blur'),
    '#default_value' => theme_get_setting($name . '_text_shadow_blur'),
  );
  // Text shadow color
  $form[$name . '_fieldset'][$name . '_text_shadow_opts'][$name . '_text_shadow_color'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#title' => t('Color'),
    '#default_value' => theme_get_setting($name . '_text_shadow_color'),
  );

  return $form;
}

/**
 * Save the background image for a custom CSS selector
 */
function enso_light_selector_bg_save(&$form, &$form_state, $name) {
  // Get the previous value
  $previous = 'public://' . $form['enso'][$name][$name . '_fieldset'][$name . '_bg_image_opts'][$name . '_bg_path']['#default_value'];
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

  // Generate layout
  if ($form_state['values'][$name . '_use_layout'])  {
    $layout_width = $form_state['values'][$name . '_layout_width'];
    $layout_height = $form_state['values'][$name . '_layout_height'];
    $layout_margins = $form_state['values'][$name . '_layout_margins'];
    $layout_padding = $form_state['values'][$name . '_layout_padding'];

    $css .= $css_selector . ' { ';
    $css .= $layout_width ? 'width: ' . $layout_width . '; ' : '';
    $css .= $layout_height ? 'height: ' . $layout_height . '; ' : '';
    $css .= $layout_margins ? 'margin: ' . $layout_margins . '; ' : '';
    $css .= $layout_padding ? 'padding: ' . $layout_padding . '; ' : '';
    $css .= ' }' . "\n";
  }

  // Generate background image
  if ($form_state['values'][$name . '_use_bg_image'])  {

    $bg_url = 'url(\'' . file_create_url($form_state['values'][$name . '_bg_path']) . '\')';
    $bg_position = $form_state['values'][$name . '_bg_position'];
    $bg_attachment = $form_state['values'][$name . '_bg_attachment'];
    $bg_repeat = $form_state['values'][$name . '_bg_repeat'];

    $css .= $css_selector . ' { ';
    $css .= 'background-image: ' . $bg_url . '; ';
    $css .= 'background-position: ' . $bg_position . '; ';
    $css .= 'background-attachment: ' . $bg_attachment . '; ';
    $css .= 'background-repeat: ' . $bg_repeat . '; ';
    $css .= ' }' . "\n";
  }

  // Generate background color
  if ($form_state['values'][$name . '_use_bg_colors'])  {
    $bg_colors = explode('|', $form_state['values'][$name . '_bg_color']);
    $bg_gradient = $form_state['values'][$name . '_bg_gradient'];
    $bg_url = $form_state['values'][$name . '_use_bg_image'] ? $bg_url . ',' : '';

    if ($bg_gradient == 'none' && count($bg_colors) >= 1) {
      $css .= $css_selector . ' { ';
      $css .= 'background-color: ' . $bg_colors[0] . ';'; // fallback
      $css .= 'background-image: ' . $bg_url . $bg_colors[0] . ';';
      $css .= 'background-image: ' . $bg_url . $bg_colors[0] . ';';
      $css .= ' }' . "\n";
    }
    else if ($bg_gradient != 'none' && count($bg_colors) > 1) {
      $bg_color_str = implode(', ', $bg_colors);
      $grad_webkit = $bg_gradient == 'left-to-right' ? 'left, ' : '';
      $grad_moz_o_ms = $bg_gradient == 'left-to-right' ? 'right, ' : '';
      $grad_standard = $bg_gradient == 'left-to-right' ? 'to right, ' : '';

      $css .= $css_selector . ' { ';
      $css .= 'background-image: ' . $bg_url . ' -webkit-linear-gradient(' . $grad_webkit . $bg_color_str . '); ';
      $css .= 'background-image: ' . $bg_url . ' -o-linear-gradient(' . $grad_moz_o_ms . $bg_color_str . '); ';
      $css .= 'background-image: ' . $bg_url . ' -ms-linear-gradient(' . $grad_moz_o_ms . $bg_color_str . '); ';
      $css .= 'background-image: ' . $bg_url . ' -moz-linear-gradient(' . $grad_moz_o_ms . $bg_color_str . '); ';
      $css .= 'background-image: ' . $bg_url . ' linear-gradient(' . $grad_standard . $bg_color_str . ');';
      $css .= ' }' . "\n";
    }
  }

  // Generate foreground color
  if ($form_state['values'][$name . '_use_fg'])  {
    // Color
    $color = $form_state['values'][$name . '_color'];
    $color = $color == '' ? 'inherit' : $color;

    $css .= $css_selector . ' { ';
    $css .= 'color: ' . $color . ';';
    $css .= ' }' . "\n";
  }

  // Generate foreground link colors & decoration
  if ($form_state['values'][$name . '_use_fg'])  {
    // Link color & decoration
    $link_color = $form_state['values'][$name . '_link_color'];
    $link_color = $link_color == '' ? 'inherit' : $link_color;
    $link_decoration = $form_state['values'][$name . '_link_decoration'];

    $css .= $css_selector . ' a { ';
    $css .= 'color: ' . $link_color . '; ';
    $css .= 'text-decoration: ' . $link_decoration . ';';
    $css .= ' }' . "\n";

    // Link hover/focus color & decoration
    $hover_color = $form_state['values'][$name . '_hover_color'];
    $hover_color = $hover_color == '' ? 'inherit' : $hover_color;
    $hover_decoration = $form_state['values'][$name . '_hover_decoration'];

    $css .= $css_selector . ' a:hover, ' . $css_selector . ' a:focus { ';
    $css .= 'color: ' . $hover_color . '; ';
    $css .= 'text-decoration: ' . $hover_decoration . ';';
    $css .= ' }' . "\n";
  }

  // Generate borders
  if ($form_state['values'][$name . '_use_borders'])  {
    $border_width = $form_state['values'][$name . '_border_width'];
    if ($border_width) {
      $border_color = $form_state['values'][$name . '_border_color'];
      $border_style = $form_state['values'][$name . '_border_style'];
      $border_top = $form_state['values'][$name . '_border_top'];
      $border_right = $form_state['values'][$name . '_border_right'];
      $border_bottom = $form_state['values'][$name . '_border_bottom'];
      $border_left = $form_state['values'][$name . '_border_left'];

      $css .= $css_selector . ' { ';
      $css .= 'border-color: ' . $border_color . '; ';
      $css .= 'border-width: ' . $border_width . '; ';
      $css .= $border_top ? 'border-top-style: ' . $border_style . '; ' : '';
      $css .= $border_right ? 'border-right-style: ' . $border_style . '; ' : '';
      $css .= $border_bottom ? 'border-bottom-style: ' . $border_style . '; ' : '';
      $css .= $border_left ? 'border-left-style: ' . $border_style . ';' : '';
      $css .= ' }' . "\n";
    }
  }

  // Generate rounded corners
  if ($form_state['values'][$name . '_use_radius'])  {
    $radius = $form_state['values'][$name . '_radius'];
    if ($radius) {
      $top_left_radius = $form_state['values'][$name . '_top_left_radius'];
      $top_right_radius = $form_state['values'][$name . '_top_right_radius'];
      $bottom_right_radius = $form_state['values'][$name . '_bottom_right_radius'];
      $bottom_left_radius = $form_state['values'][$name . '_bottom_left_radius'];

      $css .= $css_selector . ' { ';
      $prefixes = array('-webkit-', '-moz-', '');
      foreach ($prefixes as $prefix) {
        $separator = ($prefix == '-moz-') ? '' : '-';
        $css .= $top_left_radius ? $prefix . 'border-top' . $separator . 'left-radius: ' . $radius . '; ' : '';
        $css .= $top_right_radius ? $prefix . 'border-top' . $separator . 'right-radius: ' . $radius . '; ' : '';
        $css .= $bottom_right_radius ? $prefix . 'border-bottom' . $separator . 'right-radius: ' . $radius . '; ' : '';
        $css .= $bottom_left_radius ? $prefix . 'border-bottom' . $separator . 'left-radius: ' . $radius . '; ' : '';
      }
      $css .= ' }' . "\n";
    }
  }

  // Generate box shadows
  if ($form_state['values'][$name . '_use_box_shadow'])  {
      $distance = $form_state['values'][$name . '_box_shadow_distance'];
      $blur = $form_state['values'][$name . '_box_shadow_blur'];
      $color = $form_state['values'][$name . '_box_shadow_color'];

      $css .= $css_selector . ' { ';
      $prefixes = array('-webkit-', '-moz-', '');
      foreach ($prefixes as $prefix) {
        $css .= $prefix . 'box-shadow: ' . $distance . ' ' . $distance . ' ' . $blur . ' ' . $color . '; ';
      }
      $css .= '}' . "\n";
  }

  // Generate text shadows
  if ($form_state['values'][$name . '_use_text_shadow'])  {
      $distance = $form_state['values'][$name . '_text_shadow_distance'];
      $blur = $form_state['values'][$name . '_text_shadow_blur'];
      $color = $form_state['values'][$name . '_text_shadow_color'];

      $css .= $css_selector . ' { ';
      $css .= 'text-shadow: ' . $distance . ' ' . $distance . ' ' . $blur . ' ' . $color . '; ';
      $css .= '}' . "\n";
  }

  return $css;
}
