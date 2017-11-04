<?php

/**
 * Returns HTML for a file upload form element.
 *
 * For assistance with handling the uploaded file correctly, see the API
 * provided by file.inc.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #name, #size, #description, #required,
 *     #attributes.
 *
 * @ingroup themeable
 */
function lim_file(&$variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'file';
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-file','hidden'));

  $item_name = $variables['element']['#name'];
  $placeholder = t('Carica File');
  $markup = '<ul class="list-inline js-upload-file" data-item ="'.$item_name.'" >';
  $markup .= '<li><div class="filename js-filename">'.$placeholder.'</div></li>';
  $markup .= '<li><p class="btn btn-default js-button-trigger-file-upload"><i class="fa fa fa-paperclip"></i> <span>Sfoglia</span></p></li>';
  $markup .='</ul>';
  return $markup.'<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Returns HTML for a form element.
 *
 * Each form element is wrapped in a DIV container having the following CSS
 * classes:
 * - form-item: Generic for all form elements.
 * - form-type-#type: The internal element #type.
 * - form-item-#name: The internal form element #name (usually derived from the
 *   $form structure and set via form_builder()).
 * - form-disabled: Only set if the form element is #disabled.
 *
 * In addition to the element itself, the DIV contains a label for the element
 * based on the optional #title_display property, and an optional #description.
 *
 * The optional #title_display property can have these values:
 * - before: The label is output before the element. This is the default.
 *   The label includes the #title and the required marker, if #required.
 * - after: The label is output after the element. For example, this is used
 *   for radio and checkbox #type elements as set in system_element_info().
 *   If the #title is empty but the field is #required, the label will
 *   contain only the required marker.
 * - invisible: Labels are critical for screen readers to enable them to
 *   properly navigate through forms but can be visually distracting. This
 *   property hides the label for everyone except screen readers.
 * - attribute: Set the title attribute on the element to create a tooltip
 *   but output no label element. This is supported only for checkboxes
 *   and radios in form_pre_render_conditional_form_element(). It is used
 *   where a visual label is not needed, such as a table of checkboxes where
 *   the row and column provide the context. The tooltip will include the
 *   title and required marker.
 *
 * If the #title property is not set, then the label and any required marker
 * will not be output, regardless of the #title_display or #required values.
 * This can be useful in cases such as the password_confirm element, which
 * creates children elements that have their own labels and required markers,
 * but the parent element should have neither. Use this carefully because a
 * field without an associated label can cause accessibility challenges.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #title_display, #description, #id, #required,
 *     #children, #type, #name.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_form_element()
 *
 * @ingroup theme_functions
 */
function lim_form_element(&$variables) {
  $element = &$variables['element'];
  $type = $element['#type'];

  $wrappers = array('width');

  foreach ($wrappers as $wrapper) {
    $settings = lim_get_theme_setting($type .'_'. $wrapper);

    if(!empty($settings)) {
      $element['#wrapper_attributes']['class'][] = 'form-control-' . $type . '-' . $wrapper;
    }
  }

  return bootstrap_form_element($variables);
}

/**
 * @param $variables
 *
 * @return string
 */
function lim_form_element_label(&$variables) {
  $element = &$variables['element'];

  // Extract variables.
  $output = '';
  $prefix = '';
  $suffix = '';

  $title = !empty($element['#title']) ? filter_xss_admin($element['#title']) : '';

  // Only show the required marker if there is an actual title to display.
  if ($title && $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '') {
    $title .= ' ' . $required;
  }

  $display = isset($element['#title_display']) ? $element['#title_display'] : 'before';
  $type = !empty($element['#type']) ? $element['#type'] : FALSE;
  $checkbox = $type && $type === 'checkbox';
  $radio = $type && $type === 'radio';

  // Immediately return if the element is not a checkbox or radio and there is
  // no label to be rendered.
  if (!$checkbox && !$radio && ($display === 'none' || !$title)) {
    return '';
  }

  // Retrieve the label attributes array.
  $attributes = &_bootstrap_get_attributes($element, 'label_attributes');

  // Add Bootstrap label class.
  $attributes['class'][] = 'control-label';

  // Add the necessary 'for' attribute if the element ID exists.
  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // Checkboxes and radios must construct the label differently.
  if ($checkbox || $radio) {
    if ($display === 'before') {
      $output .= $title;

    }
    elseif ($display === 'none' || $display === 'invisible') {
      $output .= '<span class="element-invisible">' . $title . '</span>';
    }
    // Inject the rendered checkbox or radio element inside the label.
    if (!empty($element['#children'])) {
      $output .= $element['#children'];
    }
    if ($display === 'after') {
      $output .= $title;
    }

    $prefix = '<p>'. $element['#children'];
    $suffix = '</p>';

  }
  // Otherwise, just render the title as the label.
  else {
    // Show label only to screen readers to avoid disruption in visual flows.
    if ($display === 'invisible') {
      $attributes['class'][] = 'element-invisible';
    }
    $output .= $title;
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return $prefix. ' <label' . drupal_attributes($attributes) . '>' . $output . "</label>\n" . $suffix;
}

/**
 * Returns HTML for a button form element.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #attributes, #button_type, #name, #value.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_button()
 *
 * @ingroup theme_functions
 */
function lim_button(&$variables) {
  $element = $variables['element'];

  $element['#attributes']['class'][] = 'waves-effect';
  $element['#attributes']['class'][] = 'waves-light';
  $text = $element['#value'];

  // Allow button text to be appear hidden.
  // @see https://www.drupal.org/node/2327437
  if (!empty($element['#hide_text']) || $element['#icon_position'] === 'icon_only') {
    $text = '<span class="sr-only">' . $text . '</span>';
  }

  // Add icons before or after the value.
  // @see https://www.drupal.org/node/2219965
  if (!empty($element['#icon']) && ($icon = render($element['#icon']))) {
    // Add icon position class.
    _bootstrap_add_class('icon-' . drupal_html_class($element['#icon_position'] === 'icon_only' ? 'only' : $element['#icon_position']), $element);
    if ($element['#icon_position'] === 'after') {
      $text .= ' ' . $icon;
    }
    else {
      $text = $icon . ' ' . $text;
    }
  }
  // This line break adds inherent margin between multiple buttons.
  return '<button' . drupal_attributes($element['#attributes']) . '>' . filter_xss_admin($text) . "</button>\n";
}