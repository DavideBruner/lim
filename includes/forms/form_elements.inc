<?php

/**
 * Implements form_elements theme_settings form
 *
 * @param $form
 * @param $form_state
 *
 * @return array
 */
function lim_form_elements_theme_settings_form($form, $form_state){
  $form = array();

  $form['textfield'] = array(
    '#type' => 'fieldset',
    '#title' => t('Textfield'),
    '#parents' => array('form_elements'),
  );

  $form['textfield']['textfield_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Textfield width'),
    '#description' => t('Enter the desired width of the textfield, in the unit you want px, em, %.'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('textfield_width'),
  );

  $form['textfield']['input_bg'] = array(
    '#type' => 'textfield',
    '#title' => t('Input Background'),
    '#description' => t('Enter the Background color of the input elements.'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('textfield_width'),
  );

  $form['textfield']['input_bg_disabled'] = array(
    '#type' => 'textfield',
    '#title' => t('Input Background Disabled'),
    '#description' => t('Enter the Background color of disabled input elements.'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('textfield_width'),
    '#less_variable' => '@input-bg-disabled'
  );

  $form['textfield']['input_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Input background color'),
    '#description' => t('Enter the background color for the inputs elements.'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('input_color'),
  );

  $form['textfield']['input_color_placeholder'] = array(
    '#type' => 'textfield',
    '#title' => t('Placeholder text color'),
    '#description' => t('Enter the placeholder color for the input elements.'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('input_color_placeholder'),
  );

  $form['textfield']['input_border_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Input Border Color'),
    '#description' => t('Enter the desired width of the textfield, in the unit you want px, em, %.'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('input_border_color'),
  );

  $form['textfield']['input_border_radius'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Border Radius'),
    '#description' => t('Default `.form-control` border radius'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('input_border_radius'),
  );

  $form['textfield']['input_border_focus'] = array(
    '#type' => 'textfield',
    '#title' => t('Border Focus'),
    '#description' => t('Border color for inputs on focus'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('input_border_focus'),
  );

  $form['textfield']['input_height_base'] = array(
    '#type' => 'textfield',
    '#title' => t('Input height base'),
    '#description' => t('Default `.form-control` height'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('input_height_base'),
  );

  $form['textfield']['input_height_large'] = array(
    '#type' => 'textfield',
    '#title' => t('Input height base large'),
    '#description' => t('Large `.form-control` height'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('input_height_large'),
  );

  $form['textfield']['input_height_small'] = array(
    '#type' => 'textfield',
    '#title' => t('Input height base small'),
    '#description' => t('Small `.form-control` height'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('input_height_small'),
  );

  $form['select'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select'),
    '#parents' => array('form_elements'),
  );

  $form['select']['select_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Select width'),
    '#description' => t('Enter the desired width of the select, in the unit you want px, em, %.'),
    '#required' => FALSE,
    '#default_value' => lim_get_theme_setting('select_width'),
  );

  $form['radio'] = array(
    '#type' => 'fieldset',
    '#title' => t('Radio'),
    //'#group' => 'form_elements',
    '#parents' => array('form_elements'),
  );

  return $form;
}

/*
 * Implements form_elements theme_settings form submit
 */
function lim_form_elements_theme_settings_form_submit($form, $form_state){
  dpm($form);
  dpm($form_state);

  foreach ($form_state['values']['form_elements'] as $variable => $value) {
    dpm($variable);
    dpm($value);
  }
}