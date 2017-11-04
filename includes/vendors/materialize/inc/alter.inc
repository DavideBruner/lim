<?php

/**
 * Implements hook_vendors_setting_form_alter().
 */
function lim_vendors_setting_form_alter(&$vendors) {}

/**
 * Alter LESS variables provided by other modules or themes.
 *
 * This is called before hook_less_variables_SYSTEM_NAME_alter().
 *
 * @param &string[] $less_variables
 *   Flat associative array of variables, where key is variable name.
 * @param string    $system_name
 *   A string of the system_name of the module or theme that this applies to.
 *
 * @see hook_less_variables()
 * @see hook_less_variables_SYSTEM_NAME_alter()
 */
function lim_less_variables_alter(array &$less_variables, $system_name) {
  // Get the current state of the theme setting variable 'materialize_less'
  // and set it as the conditional variable @materialize-enabled
  // used to import the materialize.less library in style.less
  // @see .conditional-import() in mixins.less
  // @see materialize.less
  // @see style.less
  $less_variables['@materialize-enabled'] = lim_get_theme_setting('materialize_less');
  $less_variables['@textfield-width'] = lim_get_theme_setting('textfield_width');
}

/**
 * @param $info
 */
function lim_element_info_alter(&$info){
  //------------------------------ Check if label materialize is enable ----------
  $enable_label_materialize = lim_get_theme_setting('materialize_label');
  $enable_label_materialize = ($enable_label_materialize == 1) ? TRUE : FALSE;
  //------------------------------ ./Check if label materialize is enable --------

  if( $enable_label_materialize ){
    if(isset($info['textfield']) && !empty($info['textfield'])){
      $info['textfield']['#input_type'] = 'textfield';
    }

    if(isset($info['date_text']) && !empty($info['date_text'])){
      $info['date_text']['#process'][] = 'lim_form_element_date_text_process';
    }

    if(isset($info['date_popup']) && !empty($info['date_popup'])){
      //@todo non gestita correttamente
      $info['date_popup']['#theme_wrappers'] = array('date_text');
      $info['date_popup']['#process'][] = 'lim_form_element_date_popup_process';
    }
  }
}