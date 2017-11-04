<?php
/**
 * @file
 * List of common helper functions for use in Bootstrap based themes.
 */

require_once 'common.inc';

/**
 * Iterate through all vendors array children.
 *
 * @see vendors_setting_form()
 * @see vendors_setting_form_alter()
 *
 **/

/** TODO Obtain .inc files by global vendors settings and provide an update callback for the settings update_vendors_settings() */
function _theme_include_vendors($theme = NULL){

  if(is_null($theme)) {
    $theme = _get_current_theme();
  }

  $vendors = get_theme_vendors($theme);
  if(!empty($vendors) && is_array($vendors)) {
    foreach ($vendors as $vendor_id => $vendor_settings) {
      _theme_include_vendor($theme, $vendor_id);
    }
  }

}

/**
 * Include the vendor's library it the form settings variable is checked.
 *
 * @param string $theme
 *    global theme machine_name.
 * @param string $vendor
 *    vendor machine_name used to check if enabled
 *    and include the vendor_machine_name.inc library
 *    used to define vendor's functions.
 *
 **/
function _theme_include_vendor($theme, $vendor_id) {
  if(theme_get_setting($vendor_id . '_active', $theme)) {
    $library = theme_get_setting($vendor_id . '_inc', $theme);
    if(file_exists($library)) {
      include_once $library;
    }
  }
}


/*
 * Define vendors array, used to display vendors settings in
 * the system_theme_settings_form
 *
 * Examples of usage in alternative form elements definition
 * 'components' => array(
 * '#type' => 'fieldset',
 * '#title' => t('Components'),
 * '#collapsible' => TRUE,
 * '#collapsed' => TRUE,
 *  'buttons' => array(),
 *  'navbar' => array(
 *    '#type' => 'checkbox',
 *    '#title' => t('Do you want a .fixed-top navbar?')
 *    '#default_value' => theme_get_setting('navbar'),),
 *  'badges' => array(),
 * ):
 *
 */
function vendor_settings_form($vendor_id, $form, $form_state = array()){
  $form = [];
  $callback = $vendor_id . '_vendor_settings_form';

  if(isset($vendor_id) && function_exists($callback)) {
    $form[$vendor_id] = call_user_func($callback, $form, $form_state);
  }

  //Use this hook_alter to define new $vendors array
  drupal_alter('vendors_settings_form', $form, $form_state);

  return $form;
}

/**
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function materialize_vendor_settings_form($form, $form_state){

  $form['materialize_less'] = array(
    '#type' => 'checkbox',
    '#title' => t('Less Styles'),
    '#description' => t('Include materialize.css stylesheets, processed with less. See <a href="!url">Materialize.css</a>', array(
        '!url' => 'http://materializecss.com/getting-started.html',
      )
    ),
    '#default_value' => lim_get_theme_setting('materialize_less'),
    '#states'        => array(
      // Show only if placement in "content" selected
      'visible' => array(
        ':input[name="materialize_active"]' => array(
          'checked' => TRUE
        ),
      ),
    ),
  );

  return $form;
}

/**
 * @param null $theme
 *
 * @return mixed
 */
function get_theme_vendors($theme = NULL){
  static $vendors;

  if (!isset($vendors)) {
    $vendors['cache'] = &drupal_static(__FUNCTION__);
  }

  if(is_null($theme)) {
    $theme = _get_current_theme();
  }

  $info = &$vendors['cache'];

  if (!isset($info[$theme])) {
    /* Obtain Vendors from .info file */
    $info[$theme] = get_theme_info_vendors($theme);

    /* Obtain Vendors from theme_vendors_info() */
    $callback = $theme . '_vendors_info';

    if(function_exists($callback)) {
      $info_callback_results = call_user_func($callback, $info[$theme]);
      $info[$theme] = array_replace_recursive($info[$theme], $info_callback_results);
    }
    /* hook_vendors_info_alter */
    drupal_alter('vendors_info', $info);
  }

  return $info[$theme];
}

/**
 * @param $theme
 * @param $vendor_id
 */
function update_vendors_settings($theme, $vendor_id, $settings){}

/**
 * @param $theme
 *
 * @return null
 */
function get_theme_info_vendors($theme){

  if(isset($theme)) {
    $info_file = _get_theme_info($theme);
    if(isset($info_file['vendors'])) {
      return $info_file['vendors'];
    }
  }

  return NULL;
}

