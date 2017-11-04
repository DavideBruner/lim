<?php

define('WORKING_THEME', _get_current_theme());

/*
 *  Include all the files relative to /inc directory
 *
 *  alter.inc       // hook_alters
 *  process.inc     // all process functions
 *  theme.inc       // theme functions override
 */

lim_include_base_themes_files(array('includes/vendors/materialize/inc'));