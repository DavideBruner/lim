<?php

define('LESS_THEME_ENGINE', 'less.php');
define('LESS_THEME_LIBRARY', 'less.php');

lim_less_init();

/**
 * @param string $library
 */
function lim_less_init(){
  //enable less module
  if(module_enable(array('less'))){
    lim_default_less_settings();
    //Detect library lessphp
    lim_detect_less_library();
    //Flush less caches
    less_flush_caches();
  } else {
    drupal_set_message('An error occurred enabling the <em>Less</em> module','error');
  }
}

/**
 * @param bool $restore_default
 *
 * @return array
 */
function lim_default_less_settings($restore_default = FALSE){
  $default_settings = ['less_engine' => LESS_THEME_ENGINE, 'less_devel' => 1, 'less_source_maps' => 1, 'less_watch' => 1];
  $settings = [];

  foreach ($default_settings as $setting => $default_value) {
    // Restore Default less settings flag
    if($restore_default) {
      variable_set($setting, $default_value);
    }

    $value = variable_get($setting, $default_value);
    $settings[$setting] = $value;
  }
  return $settings;
}

/**
 * @param string $library
 */
function lim_detect_less_library($library = LESS_THEME_LIBRARY){
  $library_info = libraries_detect(LESS_THEME_LIBRARY);
  if(isset($library_info['error message']) && !empty($library_info['error message'])){
    drupal_set_message($library_info['error message'],'error');
  }
}
