<?php

/**
 * @file
 * Provides frequently used functions that get theme info, settings and
 * other data.
 */

/**
 * Retrieve a setting for the current theme or for a given theme.
 *
 * lim wrapper of theme_get_setting().
 * Why? Because it wayfasterbetter, emphasis on the faster which is really the
 * only valid reason to do something as stupid as this, and it is faster,
 * considerably faster. Doing this wiped 100ms off page generation time.
 *
 * @param $setting_name
 * @param null $theme
 * @see http://api.drupal.org/api/drupal/includes!theme.inc/function/theme_get_setting/7
 */
function lim_get_theme_setting($setting_name, $theme = NULL, $default_value = NULL) {
  $cache = &drupal_static(__FUNCTION__, array());

  // If no key is given, use the current theme if we can determine it.
  if (!isset($theme)) {
    $theme = _get_current_theme();
  }

  if (empty($cache[$theme])) {

    // Get the values for the theme-specific settings from the .info files
    if ($theme) {
      $themes = list_themes();
      $theme_keys = lim_get_theme_base_themes($theme);

      foreach ($theme_keys as $theme_key) {
        if (!empty($themes[$theme_key]->info['settings'])) {
          $cache[$theme] = $themes[$theme_key]->info['settings'];
        }
      }

      // Get the saved theme-specific settings from the database.
      $var = variable_get('theme_' . $theme . '_settings', $default_value);
      if(is_array($var)) {
        $cache[$theme] = array_merge($cache[$theme], $var);
      }

    }
  }

  return isset($cache[$theme][$setting_name]) ? $cache[$theme][$setting_name] : $default_value;
}

/**
 * Return the info file array for a particular theme, usually the active theme.
 * Simple wrapper function for list_themes().
 *
 * @param $theme_name
 */
function _get_theme_info($theme_name) {
  $info = &drupal_static(__FUNCTION__, array());
  if (empty($info)) {
    $lt = list_themes();
    foreach ($lt as $key => $value) {
      if ($theme_name == $key) {
        $info = $lt[$theme_name]->info;
      }
    }
  }

  return $info;
}

/**
 * @param $directories
 *   array of directory names
 * @param $module_name
 * @param $file_extension
 *   i.e. 'inc'
 */
function lim_include_files($directories, $type, $name, $file_extension = 'inc', $recurse = TRUE) {
  $path = drupal_get_path($type, $name);

  // Include all files with given extension.
  foreach ($directories as $dir_name) {
    $files = file_scan_directory($path . '/' . $dir_name, '/.*\.' . $file_extension .'$/', ['recurse' => $recurse]);
    foreach ($files as $file) {
      require_once ($path . '/' . $dir_name . '/' . $file->name . '.' . $file_extension);
    }
  }
}

/**
 * @param $directories
 * @param $theme
 * @param string $file_extension
 * @param bool $recurse
 */
function lim_include_base_themes_files($directories, $theme = FALSE, $file_extension = 'inc', $recurse = FALSE){
  if(!$theme) {
    $theme = _get_current_theme();
  }
  $themes = lim_get_theme_base_themes($theme);
  foreach ($themes as $theme) {
    lim_include_files($directories, 'theme', $theme, $file_extension, $recurse);
  }
}

/**
 * @param $directories
 * @param $type
 * @param $name
 * @param $file_extension
 * @param $exclude_files
 */
function lim_directory_files_list($directory, $type, $name, $file_extension, $recurse = TRUE, $exclude_files = []) {
  $path = drupal_get_path($type, $name);
  $files = file_scan_directory($path . '/' . $directory, '/.*\.' . $file_extension . '$/', ['recurse' => $recurse]);
  return $files ? $files : NULL;
}

/**
 * Replace strings in a file.
 */
function lim_file_str_replace($file_path, $find, $replace) {
  $file_path = drupal_get_normal_path($file_path);
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  return file_put_contents($file_path, $file_contents);
}


/**
 * @return mixed|null
 */
function _get_current_theme(){
  $theme = !empty($GLOBALS['theme_key']) ? $GLOBALS['theme_key'] : NULL;
  return $theme;
}

/**
 * @param $theme
 */
function lim_get_theme_base_themes($theme){
  $themes = list_themes();
  $theme_keys = array();

  if(isset($themes[$theme])) {
    $theme_object = $themes[$theme];
    // Create a list which includes the current theme and all its base themes.
    if (isset($theme_object->base_themes)) {
      $theme_keys = array_keys($theme_object->base_themes);
      $theme_keys[] = $theme;
    }
    else {
      $theme_keys = array($theme);
    }
  }
  return $theme_keys;
}