<?php
/**
 * @file
 * The primary PHP file for this theme.
 */

$theme_path = drupal_get_path('theme', 'lim');
include_once($theme_path . '/includes/common.inc');       // get theme info, settings, css etc

/*
 *  Include all the files relative to /includes and /inc directories
 *  of base theme and subthemes
 *
 *    includes/alter.inc       // hook_alters
 *    includes/less.inc        // less css processor helper functions
 *    includes/preprocess.inc  // all preprocess functions
 *    includes/process.inc'    // all process functions
 *    includes/theme.inc'      // theme function overrides
 *    includes/vendors.inc     // the vendors system with wrapper and helper functions
 */
lim_include_base_themes_files(array('includes', 'inc'));

// If are defined vendors for the current theme they will be included once
if(function_exists('_theme_include_vendors')) {
  _theme_include_vendors();
}
