<?php

/**
 * @file
 * Functions to build subforms, save background image and generate CSS for a custom CSS selector
 */


/**
 * Build the subform for a custom CSS selector
 */
function enso_light_selector_form($css_selector, $css_selector_name) {

  $css_length_units = drupal_map_assoc(array('px', 'pt', 'in', 'cm', 'mm', 'pc', 'em', 'ex', '%'));
  $css_auto_or_other = array(
      'unspecified' => '',
      'auto' => t('Auto'),
      'other' => t('Other ...'),
  );

  $name = preg_replace('/[^a-z0-9]+/', '_', strtolower($css_selector_name));

  $form = array();

  $form[$name . '_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Styling for "' . $css_selector_name . '"'),
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
  $form[$name . '_fieldset']['layout_options'] = array(
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
  $form[$name . '_fieldset']['layout_options'][$name . '_width_cont'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Width</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_width_cont'][$name . '_width'] = array(
    '#type' => 'select',
    '#options' => $css_auto_or_other,
    '#default_value' => theme_get_setting($name . '_width'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_width_cont'][$name . '_width_val'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_width"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_width_val'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_width_cont'][$name . '_width_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_width"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_width_unit'),
  );
  // Height
  $form[$name . '_fieldset']['layout_options'][$name . '_height_cont'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Height</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_height_cont'][$name . '_height'] = array(
    '#type' => 'select',
    '#options' => $css_auto_or_other,
    '#default_value' => theme_get_setting($name . '_height'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_height_cont'][$name . '_height_val'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_height"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_height_val'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_height_cont'][$name . '_height_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_height"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_height_unit'),
  );
  // Margin top
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_top_cont'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Margins</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_top_cont'][$name . '_margin_top'] = array(
    '#type' => 'select',
    '#title' => 'Top',
    '#options' => $css_auto_or_other,
    '#default_value' => theme_get_setting($name . '_margin_top'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_top_cont'][$name . '_margin_top_val'] = array(
    '#type' => 'textfield',
    '#title' => 'Top margin value',
    '#title_display' => 'invisible',
    '#element_validate' => array('element_validate_number'),
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_margin_top"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_margin_top_val'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_top_cont'][$name . '_margin_top_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_margin_top"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_margin_top_unit'),
  );
  // Margin right
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_right_cont'] = array(
    '#type' => 'container',
    //'#prefix' => '<label>Right margin</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_right_cont'][$name . '_margin_right'] = array(
    '#type' => 'select',
    '#title' => 'Right',
    '#options' => $css_auto_or_other,
    '#default_value' => theme_get_setting($name . '_margin_right'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_right_cont'][$name . '_margin_right_val'] = array(
    '#type' => 'textfield',
    '#title' => 'Right margin value',
    '#title_display' => 'invisible',
    '#element_validate' => array('element_validate_number'),
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_margin_right"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_margin_right_val'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_right_cont'][$name . '_margin_right_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_margin_right"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_margin_right_unit'),
  );
  // Margin bottom
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_bottom_cont'] = array(
    '#type' => 'container',
    //'#prefix' => '<label>Bottom margin</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_bottom_cont'][$name . '_margin_bottom'] = array(
    '#type' => 'select',
    '#title' => 'Bottom',
    '#options' => $css_auto_or_other,
    '#default_value' => theme_get_setting($name . '_margin_bottom'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_bottom_cont'][$name . '_margin_bottom_val'] = array(
    '#type' => 'textfield',
    '#title' => 'Bottom margin value',
    '#title_display' => 'invisible',
    '#element_validate' => array('element_validate_number'),
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_margin_bottom"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_margin_bottom_val'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_bottom_cont'][$name . '_margin_bottom_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_margin_bottom"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_margin_bottom_unit'),
  );
  // Margin left
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_left_cont'] = array(
    '#type' => 'container',
    //'#prefix' => '<label>Left margin</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_left_cont'][$name . '_margin_left'] = array(
    '#type' => 'select',
    '#title' => 'Left',
    '#options' => $css_auto_or_other,
    '#default_value' => theme_get_setting($name . '_margin_left'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_left_cont'][$name . '_margin_left_val'] = array(
    '#type' => 'textfield',
    '#title' => 'Left margin value',
    '#title_display' => 'invisible',
    '#element_validate' => array('element_validate_number'),
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_margin_left"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_margin_left_val'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_margin_left_cont'][$name . '_margin_left_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_margin_left"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_margin_left_unit'),
  );
  // Padding top
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_top_cont'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Top padding</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_top_cont'][$name . '_padding_top'] = array(
    '#type' => 'select',
    '#options' => $css_auto_or_other,
    '#default_value' => theme_get_setting($name . '_padding_top'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_top_cont'][$name . '_padding_top_val'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_padding_top"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_padding_top_val'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_top_cont'][$name . '_padding_top_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_padding_top"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_padding_top_unit'),
  );
  // Padding right
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_right_cont'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Right padding</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_right_cont'][$name . '_padding_right'] = array(
    '#type' => 'select',
    '#options' => $css_auto_or_other,
    '#default_value' => theme_get_setting($name . '_padding_right'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_right_cont'][$name . '_padding_right_val'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_padding_right"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_padding_right_val'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_right_cont'][$name . '_padding_right_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_padding_right"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_padding_right_unit'),
  );
  // Padding bottom
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_bottom_cont'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Bottom padding</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_bottom_cont'][$name . '_padding_bottom'] = array(
    '#type' => 'select',
    '#options' => $css_auto_or_other,
    '#default_value' => theme_get_setting($name . '_padding_bottom'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_bottom_cont'][$name . '_padding_bottom_val'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_padding_bottom"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_padding_bottom_val'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_bottom_cont'][$name . '_padding_bottom_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_padding_bottom"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_padding_bottom_unit'),
  );
  // Padding left
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_left_cont'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Left padding</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_left_cont'][$name . '_padding_left'] = array(
    '#type' => 'select',
    '#options' => $css_auto_or_other,
    '#default_value' => theme_get_setting($name . '_padding_left'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_left_cont'][$name . '_padding_left_val'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_padding_left"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_padding_left_val'),
  );
  $form[$name . '_fieldset']['layout_options'][$name . '_padding_left_cont'][$name . '_padding_left_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_padding_left"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_padding_left_unit'),
  );

  // Use background colors checkbox
  $form[$name . '_fieldset'][$name . '_use_bg_colors'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use background color'),
    '#default_value' => theme_get_setting($name . '_use_bg_colors'),
    '#tree' => FALSE,
  );
  // Background color options fieldset
  $form[$name . '_fieldset']['bg_color_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Background color options'),
    '#states' => array(
      // Hide background colors by default
      'invisible' => array(
        'input[name="' . $name . '_use_bg_colors"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Background colors container
  $form[$name . '_fieldset']['bg_color_options']['container'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Background colors</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  // Background color 1
  $form[$name . '_fieldset']['bg_color_options']['container'][$name . '_bg_color_1'] = array(
    '#type' => 'textfield',
    '#default_value' => theme_get_setting($name . '_bg_color_1'),
    '#attributes' => array('class' => array('spectrum')), 
  );
  // Background color 2
  $form[$name . '_fieldset']['bg_color_options']['container'][$name . '_bg_color_2'] = array(
    '#type' => 'textfield',
    '#default_value' => theme_get_setting($name . '_bg_color_2'),
    '#attributes' => array('class' => array('spectrum')), 
  );
  // Background color 3
  $form[$name . '_fieldset']['bg_color_options']['container'][$name . '_bg_color_3'] = array(
    '#type' => 'textfield',
    '#default_value' => theme_get_setting($name . '_bg_color_3'),
    '#attributes' => array('class' => array('spectrum')), 
  );
  // Background color 4
  $form[$name . '_fieldset']['bg_color_options']['container'][$name . '_bg_color_4'] = array(
    '#type' => 'textfield',
    '#default_value' => theme_get_setting($name . '_bg_color_4'),
    '#attributes' => array('class' => array('spectrum')), 
  );
  // Background color 5
  $form[$name . '_fieldset']['bg_color_options']['container'][$name . '_bg_color_5'] = array(
    '#type' => 'textfield',
    '#default_value' => theme_get_setting($name . '_bg_color_5'),
    '#attributes' => array('class' => array('spectrum')), 
  );
  // Background gradient direction
  $form[$name . '_fieldset']['bg_color_options'][$name . '_bg_gradient'] = array(
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
  $form[$name . '_fieldset']['bg_image_options'] = array(
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
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to background image'),
    '#default_value' => $bg_path,
    '#disabled' => TRUE,
  );
  // Background image upload field
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload background image'),
    '#description' => t('Upload a new image for the background.'),
  );
  // Background position (X)
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_pos_x_cont'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Background position (X)</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_pos_x_cont'][$name . '_bg_pos_x'] = array(
    '#type' => 'select',
    '#options' => array(
      'left' => t('Left'),
      'center' => t('Center'),
      'right' => t('Right'),
      'other' => t('Other ...'),
    ),
    '#default_value' => theme_get_setting($name . '_bg_pos_x'),
  );
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_pos_x_cont'][$name . '_bg_pos_x_val'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_bg_pos_x"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_bg_pos_x_val'),
  );
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_pos_x_cont'][$name . '_bg_pos_x_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_bg_pos_x"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_bg_pos_x_unit'),
  );
  // Background position (Y)
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_pos_y_cont'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Background position (Y)</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_pos_y_cont'][$name . '_bg_pos_y'] = array(
    '#type' => 'select',
    '#options' => array(
      'top' => t('Top'),
      'center' => t('Center'),
      'bottom' => t('Bottom'),
      'other' => t('Other ...'),
    ),
    '#default_value' => theme_get_setting($name . '_bg_pos_y'),
  );
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_pos_y_cont'][$name . '_bg_pos_y_val'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_bg_pos_y"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_bg_pos_y_val'),
  );
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_pos_y_cont'][$name . '_bg_pos_y_unit'] = array(
    '#type' => 'select',
    '#options' => $css_length_units,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $name . '_bg_pos_y"]' => array('value' => 'other'),
      ),
    ),
    '#default_value' => theme_get_setting($name . '_bg_pos_y_unit'),
  );
  // Background repeat
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_repeat'] = array(
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
  $form[$name . '_fieldset']['bg_image_options'][$name . '_bg_attachment'] = array(
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
  $form[$name . '_fieldset']['fg_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Foreground options'),
    '#states' => array(
      // Hide foreground colors fieldset by default
      'invisible' => array(
        'input[name="' . $name . '_use_fg"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Text color
  $form[$name . '_fieldset']['fg_options'][$name . '_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text color'),
    '#default_value' => theme_get_setting($name . '_text_color'),
    '#attributes' => array('class' => array('spectrum')), 
  );
  // Text decoration
  $form[$name . '_fieldset']['fg_options'][$name . '_text_decoration'] = array(
    '#type' => 'select',
    '#title' => t('Text decoration'),
    '#options' => array(
      'inherit' => t('Inherit'),
      'none' => t('None'),
      'underline' => t('Underline'),
      'overline' => t('Overline'),
      'line-through' => t('Line-through'),
    ),
    '#default_value' => theme_get_setting($name . '_text_decoration'),
  );

  // Use borders checkbox
  $form[$name . '_fieldset'][$name . '_use_borders'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use borders'),
    '#default_value' => theme_get_setting($name . '_use_borders'),
    '#tree' => FALSE,
  );
  // Border options fieldset
  $form[$name . '_fieldset']['border_options'] = array(
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
  $form[$name . '_fieldset']['border_options'][$name . '_border_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Border color'),
    '#default_value' => theme_get_setting($name . '_border_color'),
    '#attributes' => array('class' => array('spectrum')), 
  );
  // Border width
  $form[$name . '_fieldset']['border_options'][$name . '_border_width'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Border width'),
    '#default_value' => theme_get_setting($name . '_border_width'),
  );
  // Border style
  $form[$name . '_fieldset']['border_options'][$name . '_border_style'] = array(
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
  $form[$name . '_fieldset']['border_options'][$name . '_borders_container'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Apply borders to</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  // Borders top
  $form[$name . '_fieldset']['border_options'][$name . '_borders_container'][$name . '_border_top'] = array(
    '#type' => 'checkbox',
    '#title' => t('Top'),
    '#default_value' => theme_get_setting($name . '_border_top'),
  );
  // Borders right
  $form[$name . '_fieldset']['border_options'][$name . '_borders_container'][$name . '_border_right'] = array(
    '#type' => 'checkbox',
    '#title' => t('Right'),
    '#default_value' => theme_get_setting($name . '_border_right'),
  );
  // Borders bottom
  $form[$name . '_fieldset']['border_options'][$name . '_borders_container'][$name . '_border_bottom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bottom'),
    '#default_value' => theme_get_setting($name . '_border_bottom'),
  );
  // Borders left
  $form[$name . '_fieldset']['border_options'][$name . '_borders_container'][$name . '_border_left'] = array(
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
  $form[$name . '_fieldset']['radius_options'] = array(
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
  $form[$name . '_fieldset']['radius_options'][$name . '_radius'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Rounded corner radius'),
    '#default_value' => theme_get_setting($name . '_radius'),
  );
  // Rounded corners container
  $form[$name . '_fieldset']['radius_options'][$name . '_radius_container'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Apply rounded corners to</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  // Rounded corner radius top-left
  $form[$name . '_fieldset']['radius_options'][$name . '_radius_container'][$name . '_top_left_radius'] = array(
    '#type' => 'checkbox',
    '#title' => t('Top-left'),
    '#default_value' => theme_get_setting($name . '_top_left_radius'),
  );
  // Rounded corner radius top-right
  $form[$name . '_fieldset']['radius_options'][$name . '_radius_container'][$name . '_top_right_radius'] = array(
    '#type' => 'checkbox',
    '#title' => t('Top-right'),
    '#default_value' => theme_get_setting($name . '_top_right_radius'),
  );
  // Rounded corner radius bottom-right
  $form[$name . '_fieldset']['radius_options'][$name . '_radius_container'][$name . '_bottom_right_radius'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bottom-right'),
    '#default_value' => theme_get_setting($name . '_bottom_right_radius'),
  );
  // Rounded corner radius bottom-left
  $form[$name . '_fieldset']['radius_options'][$name . '_radius_container'][$name . '_bottom_left_radius'] = array(
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
  $form[$name . '_fieldset']['box_shadow_options'] = array(
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
  $form[$name . '_fieldset']['box_shadow_options'][$name . '_box_shadow_distance'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Distance'),
    '#default_value' => theme_get_setting($name . '_box_shadow_distance'),
  );
  // Box shadow blur
  $form[$name . '_fieldset']['box_shadow_options'][$name . '_box_shadow_blur'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Blur'),
    '#default_value' => theme_get_setting($name . '_box_shadow_blur'),
  );
  // Box shadow color
  $form[$name . '_fieldset']['box_shadow_options'][$name . '_box_shadow_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Color'),
    '#default_value' => theme_get_setting($name . '_box_shadow_color'),
    '#attributes' => array('class' => array('spectrum')), 
  );
  
  // Use text shadow checkbox
  $form[$name . '_fieldset'][$name . '_use_text_shadow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use text shadow'),
    '#default_value' => theme_get_setting($name . '_use_text_shadow'),
    '#tree' => FALSE,
  );
  // Text shadow options fieldset
  $form[$name . '_fieldset']['text_shadow_options'] = array(
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
  $form[$name . '_fieldset']['text_shadow_options'][$name . '_text_shadow_distance'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Distance'),
    '#default_value' => theme_get_setting($name . '_text_shadow_distance'),
  );
  // Text shadow blur
  $form[$name . '_fieldset']['text_shadow_options'][$name . '_text_shadow_blur'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Blur'),
    '#default_value' => theme_get_setting($name . '_text_shadow_blur'),
  );
  // Text shadow color
  $form[$name . '_fieldset']['text_shadow_options'][$name . '_text_shadow_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Color'),
    '#default_value' => theme_get_setting($name . '_text_shadow_color'),
    '#attributes' => array('class' => array('spectrum')), 
  );

  // Use transition
  $form[$name . '_fieldset'][$name . '_use_transition'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use transition'),
    '#default_value' => theme_get_setting($name . '_use_transition'),
    '#tree' => FALSE,
  );
  // Transition options fieldset
  $form[$name . '_fieldset']['transition_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Transition options'),
    '#states' => array(
      // Hide transition fieldset by default
      'invisible' => array(
        'input[name="' . $name . '_use_transition"]' => array('checked' => FALSE),
      ),
    ),
  );
  // Transition duration
  $form[$name . '_fieldset']['transition_options'][$name . '_transition_duration'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Duration'),
    '#default_value' => theme_get_setting($name . '_transition_duration'),
  );
  // Transition delay
  $form[$name . '_fieldset']['transition_options'][$name . '_transition_delay'] = array(
    '#type' => 'textfield',
    '#size' => '5',
    '#title' => t('Delay'),
    '#default_value' => theme_get_setting($name . '_transition_delay'),
  );
  // Transition function
  $form[$name . '_fieldset']['transition_options'][$name . '_transition_function'] = array(
    '#type' => 'select',
    '#title' => t('Function'),
    '#options' => array(
      'ease' => t('Ease'),
      'linear' => t('Linear'),
      'ease-in' => t('Ease-in'),
      'ease-out' => t('Ease-out'),
      'ease-in-out' => t('Ease-in-out'),
    ),
    '#default_value' => theme_get_setting($name . '_transition_function'),
  );
  // Transition container
  $form[$name . '_fieldset']['transition_options'][$name . '_transition_container'] = array(
    '#type' => 'container',
    '#prefix' => '<label>Apply transition to</label>',    
    '#attributes' => array('class' => array('container-inline')), 
  );
  // Transition color
  $form[$name . '_fieldset']['transition_options'][$name . '_transition_container'][$name . '_transition_fg_color'] = array(
    '#type' => 'checkbox',
    '#title' => t('Color'),
    '#default_value' => theme_get_setting($name . '_transition_fg_color'),
  );
  // Transition background color
  $form[$name . '_fieldset']['transition_options'][$name . '_transition_container'][$name . '_transition_bg_color'] = array(
    '#type' => 'checkbox',
    '#title' => t('Background color'),
    '#default_value' => theme_get_setting($name . '_transition_bg_color'),
  );

  return $form;
}

/**
 * Save the background image for a custom CSS selector
 */
function enso_light_selector_bg_save(&$form, &$form_state, $css_selector_name) {

  $name = preg_replace('/[^a-z0-9]+/', '_', strtolower($css_selector_name));

  // Get the previous value
  $previous = 'public://' . $form['enso'][$name][$name . '_fieldset']['bg_image_options'][$name . '_bg_path']['#default_value'];
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
function enso_light_selector_generate_css(&$form_state, $css_selector, $css_selector_name) {

  $settings = $form_state['values'];
  $name = preg_replace('/[^a-z0-9]+/', '_', strtolower($css_selector_name));

  $tab = "  ";
  $eol = ";\n";

  $css = '';

/*
  $use_layout = $settings[$name . '_use_layout'];
  $use_bg_image = $settings[$name . '_use_bg_image'];
  $use_bg_colors = $settings[$name . '_use_bg_colors'];
  $use_fg = $settings[$name . '_use_fg'];
  $use_borders = $settings[$name . '_use_borders'];
  $use_radius = $settings[$name . '_use_radius'];
  $use_box_shadow = $settings[$name . '_use_box_shadow'];
  $use_text_shadow = $settings[$name . '_use_text_shadow'];
  $use_transition = $settings[$name . '_use_transition'];
*/

  if ($settings[$name . '_use_layout'] || $settings[$name . '_use_bg_image'] || $settings[$name . '_use_bg_colors'] || $settings[$name . '_use_fg'] || $settings[$name . '_use_borders'] || $settings[$name . '_use_radius'] || $settings[$name . '_use_box_shadow'] || $settings[$name . '_use_text_shadow'] || $settings[$name . '_use_transition']) {

    $css .= $css_selector . " {\n";

    // Generate layout
    if ($settings[$name . '_use_layout'])  {
      $width = _enso_light_get_css_value($settings[$name . '_width'], $settings[$name . '_width_val'], $settings[$name . '_width_unit']);
      $height = _enso_light_get_css_value($settings[$name . '_height'], $settings[$name . '_height_val'], $settings[$name . '_height_unit']);
      $margin_top = _enso_light_get_css_value($settings[$name . '_margin_top'], $settings[$name . '_margin_top_val'], $settings[$name . '_margin_top_unit']);
      $margin_right = _enso_light_get_css_value($settings[$name . '_margin_right'], $settings[$name . '_margin_right_val'], $settings[$name . '_margin_right_unit']);
      $margin_bottom = _enso_light_get_css_value($settings[$name . '_margin_bottom'], $settings[$name . '_margin_bottom_val'], $settings[$name . '_margin_bottom_unit']);
      $margin_left = _enso_light_get_css_value($settings[$name . '_margin_left'], $settings[$name . '_margin_left_val'], $settings[$name . '_margin_left_unit']);
      $padding_top = _enso_light_get_css_value($settings[$name . '_padding_top'], $settings[$name . '_padding_top_val'], $settings[$name . '_padding_top_unit']);
      $padding_right = _enso_light_get_css_value($settings[$name . '_padding_right'], $settings[$name . '_padding_right_val'], $settings[$name . '_padding_right_unit']);
      $padding_bottom = _enso_light_get_css_value($settings[$name . '_padding_bottom'], $settings[$name . '_padding_bottom_val'], $settings[$name . '_padding_bottom_unit']);
      $padding_left = _enso_light_get_css_value($settings[$name . '_padding_left'], $settings[$name . '_padding_left_val'], $settings[$name . '_padding_left_unit']);

      $css .= $width ? $tab . 'width: ' . $width . $eol : '';
      $css .= $height ? $tab . 'height: ' . $height . $eol : '';
      $css .= $margin_top ? $tab . 'margin-top: ' . $margin_top . $eol : '';
      $css .= $margin_right ? $tab . 'margin-right: ' . $margin_right . $eol : '';
      $css .= $margin_bottom ? $tab . 'margin-bottom: ' . $margin_bottom . $eol : '';
      $css .= $margin_left ? $tab . 'margin-left: ' . $margin_left . $eol : '';
      $css .= $padding_top ? $tab . 'padding-top: ' . $padding_top . $eol : '';
      $css .= $padding_right ? $tab . 'padding-right: ' . $padding_right . $eol : '';
      $css .= $padding_bottom ? $tab . 'padding-bottom: ' . $padding_bottom . $eol : '';
      $css .= $padding_left ? $tab . 'padding-left: ' . $padding_left . $eol : '';
    }

    // Generate background image
    if ($settings[$name . '_use_bg_image'])  {

      $bg_url = 'url(\'' . file_create_url($settings[$name . '_bg_path']) . '\')';

      $bg_pos_x = _enso_light_get_css_value($settings[$name . '_bg_pos_x'], $settings[$name . '_bg_pos_x_val'], $settings[$name . '_bg_pos_x_unit']);
      $bg_pos_y = _enso_light_get_css_value($settings[$name . '_bg_pos_y'], $settings[$name . '_bg_pos_y_val'], $settings[$name . '_bg_pos_y_unit']);

      $css .= $tab . 'background-image: ' . $bg_url . $eol;
      $css .= $tab . 'background-position: ' . $bg_pos_x . ' ' . $bg_pos_y . $eol;
      $css .= $tab . 'background-attachment: ' . $settings[$name . '_bg_attachment'] . $eol;
      $css .= $tab . 'background-repeat: ' . $settings[$name . '_bg_repeat'] . $eol;
    }

    // Generate background colors
    if ($settings[$name . '_use_bg_colors'])  {
      //$bg_colors = explode("\n", $settings[$name . '_bg_color']);
      //$bg_gradient = $settings[$name . '_bg_gradient'];
      $bg_colors = array();
      if ($settings[$name . '_bg_color_1']) $bg_colors[] = $settings[$name . '_bg_color_1'];
      if ($settings[$name . '_bg_color_2']) $bg_colors[] = $settings[$name . '_bg_color_2'];
      if ($settings[$name . '_bg_color_3']) $bg_colors[] = $settings[$name . '_bg_color_3'];
      if ($settings[$name . '_bg_color_4']) $bg_colors[] = $settings[$name . '_bg_color_4'];
      if ($settings[$name . '_bg_color_5']) $bg_colors[] = $settings[$name . '_bg_color_5'];
      
      $bg_url = $settings[$name . '_use_bg_image'] ? $bg_url . ',' : '';

      if ($settings[$name . '_bg_gradient'] == 'none' && count($bg_colors) >= 1) {
        $css .= $tab . 'background-color: ' . $bg_colors[0] . $eol; // fallback
        $css .= $tab . 'background-image: ' . $bg_url . $bg_colors[0] . $eol;
        $css .= $tab . 'background-image: ' . $bg_url . $bg_colors[0] . $eol;
      }
      else if ($settings[$name . '_bg_gradient'] != 'none' && count($bg_colors) > 1) {
        $bg_color_str = implode(', ', $bg_colors);
        $grad_webkit = $settings[$name . '_bg_gradient'] == 'left-to-right' ? 'left, ' : '';
        $grad_moz_o_ms = $settings[$name . '_bg_gradient'] == 'left-to-right' ? 'right, ' : '';
        $grad_standard = $settings[$name . '_bg_gradient'] == 'left-to-right' ? 'to right, ' : '';

        $css .= $tab . 'background-image: ' . $bg_url . ' -webkit-linear-gradient(' . $grad_webkit . $bg_color_str . ')' . $eol;
        $css .= $tab . 'background-image: ' . $bg_url . ' -o-linear-gradient(' . $grad_moz_o_ms . $bg_color_str . ')' . $eol;
        $css .= $tab . 'background-image: ' . $bg_url . ' -ms-linear-gradient(' . $grad_moz_o_ms . $bg_color_str . ')' . $eol;
        $css .= $tab . 'background-image: ' . $bg_url . ' -moz-linear-gradient(' . $grad_moz_o_ms . $bg_color_str . ')' . $eol;
        $css .= $tab . 'background-image: ' . $bg_url . ' linear-gradient(' . $grad_standard . $bg_color_str . ')' . $eol;
      }
    }

    // Generate foreground color
    if ($settings[$name . '_use_fg'])  {
      /*$color = $settings[$name . '_text_color'];
      $decoration = $settings[$name . '_text_decoration'];*/

      $css .= $tab . 'color: ' . $settings[$name . '_text_color'] . $eol;
      $css .= $tab . 'text-decoration: ' . $settings[$name . '_text_decoration'] . $eol;
    }

    // Generate borders
    if ($settings[$name . '_use_borders'])  {
      //$border_width = $settings[$name . '_border_width'];
      if ($settings[$name . '_border_width']) {
        /*$border_color = $settings[$name . '_border_color'];
        $border_style = $settings[$name . '_border_style'];
        $border_top = $settings[$name . '_border_top'];
        $border_right = $settings[$name . '_border_right'];
        $border_bottom = $settings[$name . '_border_bottom'];
        $border_left = $settings[$name . '_border_left'];*/

        $css .= $settings[$name . '_border_color'] ? $tab . 'border-color: ' . $settings[$name . '_border_color'] . $eol : '';
        $css .= $tab . 'border-width: ' . $settings[$name . '_border_width'] . $eol;
        $css .= $settings[$name . '_border_top'] ? $tab . 'border-top-style: ' . $settings[$name . '_border_style'] . $eol : '';
        $css .= $settings[$name . '_border_right'] ? $tab . 'border-right-style: ' . $settings[$name . '_border_style'] . $eol : '';
        $css .= $settings[$name . '_border_bottom'] ? $tab . 'border-bottom-style: ' . $settings[$name . '_border_style'] . $eol : '';
        $css .= $settings[$name . '_border_left'] ? $tab . 'border-left-style: ' . $settings[$name . '_border_style'] . $eol : '';
      }
    }

    // Generate rounded corners
    if ($settings[$name . '_use_radius'])  {
      //$radius = $settings[$name . '_radius'];
      if ($radius) {
        $top_left_radius = $settings[$name . '_top_left_radius'];
        $top_right_radius = $settings[$name . '_top_right_radius'];
        $bottom_right_radius = $settings[$name . '_bottom_right_radius'];
        $bottom_left_radius = $settings[$name . '_bottom_left_radius'];

        $prefixes = array('-webkit-', '-moz-', '');
        foreach ($prefixes as $prefix) {
          $separator = ($prefix == '-moz-') ? '' : '-';
          $css .= $tab . $top_left_radius ? $prefix . 'border-top' . $separator . 'left-radius: ' . $settings[$name . '_radius'] . $eol : '';
          $css .= $tab . $top_right_radius ? $prefix . 'border-top' . $separator . 'right-radius: ' . $settings[$name . '_radius'] . $eol : '';
          $css .= $tab . $bottom_right_radius ? $prefix . 'border-bottom' . $separator . 'right-radius: ' . $settings[$name . '_radius'] . $eol : '';
          $css .= $tab . $bottom_left_radius ? $prefix . 'border-bottom' . $separator . 'left-radius: ' . $settings[$name . '_radius'] . $eol : '';
        }
      }
    }

    // Generate box shadows
    if ($settings[$name . '_use_box_shadow'])  {
        $distance = $settings[$name . '_box_shadow_distance'];
        $blur = $settings[$name . '_box_shadow_blur'];
        $color = $settings[$name . '_box_shadow_color'];

        $prefixes = array('-webkit-', '-moz-', '');
        foreach ($prefixes as $prefix) {
          $css .= $tab . $prefix . 'box-shadow: ' . $distance . ' ' . $distance . ' ' . $blur . ' ' . $color . $eol;
        }
    }

    // Generate text shadows
    if ($settings[$name . '_use_text_shadow'])  {
        $distance = $settings[$name . '_text_shadow_distance'];
        $blur = $settings[$name . '_text_shadow_blur'];
        $color = $settings[$name . '_text_shadow_color'];

        $css .= $tab . 'text-shadow: ' . $distance . ' ' . $distance . ' ' . $blur . ' ' . $color . $eol;
    }

    // Generate transitions
    if ($settings[$name . '_use_transition'])  {
      $duration = $settings[$name . '_transition_duration'];
      $delay = $settings[$name . '_transition_delay'];
      $function = $settings[$name . '_transition_function'];
      $properties = array();
      if ($settings[$name . '_transition_fg_color']) $properties[] = 'color';
      if ($settings[$name . '_transition_bg_color']) $properties[] = 'background-color';

      $css .= $tab . 'transition-property: ' . implode(', ', $properties) . $eol;
      $css .= $tab . 'transition-duration: ' . $duration . $eol;
      $css .= $tab . 'transition-delay: ' . $delay . $eol;
      $css .= $tab . 'transition-timing-function: ' . $function . $eol;
    }

    $css .= '}' . "\n\n";
  }

  return $css;
}


function _enso_light_get_css_value($type, $value, $units) {
  // User hasn't selected anything
  if ($type == 'unspecified') {
    $css_value = '';
  }
  // User has opted to specify an arbitrary numeric value
  else if ($type == 'other') {
    if ($value) {
      $css_value = $value . $units;
    }
    else {
      $css_value = '';
    }
  }
  // User has selected a non-numeric type e.g. 'left', 'right', 'auto', 'inherit' etc
  else {
    $css_value = $type;
  }

  return $css_value; 
}