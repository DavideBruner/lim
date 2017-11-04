<?php

function lim_html_theme_settings_form($form, $form_state){
  $form = array();

  $form['meta'] = array(
    '#type' => 'fieldset',
    '#title' => t('Metatags'),
    '#parents' => array('html'),
  );

  $form['meta']['viewport'] = array(
    '#type' => 'textfield',
    '#title' => t('viewport'),
    '#default_value' => lim_get_theme_setting('viewport', NULL, 'width=device-width, initial-scale=1.0'),
  );

  $form['meta']['theme_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Theme color'),
    '#default_value' => lim_get_theme_setting('theme_color', NULL, '#ffffff'),
  );

  $form['links'] = array(
    '#type' => 'fieldset',
    '#title' => t('Links'),
    '#parents' => array('html'),
  );

  return $form;


}