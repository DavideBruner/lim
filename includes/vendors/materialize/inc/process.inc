<?php

/**
 * Alter markup date_text
 *
 * @param $element
 * @param $form_state
 * @param $form
 * @return mixed
 */
function lim_form_element_date_text_process(&$element, &$form_state, &$form){
  $field_name = $element['#field']['field_name'];
  $format = $form[$field_name][LANGUAGE_NONE][0]['value']['#instance']['widget']['settings']['input_format'];
  $element['date']['#attributes']['class'][] = 'datepicker';
  $element['date']['#attributes']['date-format-date'] = array($format);
  return $element;
}

/**
 * @TODO evento non gestito correttamente
 * @param $element
 * @param $form_state
 * @param $form
 * @return mixed
 */
function lim_form_element_date_popup_process(&$element, &$form_state, &$form){
  unset($element['#process'][3]);
  $field_name =$element['#field']['field_name'];
  $format = $form[$field_name][LANGUAGE_NONE][0]['value']['#instance']['widget']['settings']['input_format'];
  $element['date']['#attributes']['class'][] = 'datepicker';
  $element['date']['#attributes']['date-format-date'] = array($format);
  return $element;
}