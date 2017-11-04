<?php

$theme_path = drupal_get_path('theme', 'lim');
include_once($theme_path . '/includes/common.inc');       // get theme info, settings, css etc

lim_include_base_themes_files(['includes/forms', 'inc/forms']);

/**
 * Implements hook_form_FORM_ID_alter().
 */
function lim_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL) {
  global $base_theme;
  $base_theme = _get_current_theme();
  $form_files = [];

  $form[$base_theme][$base_theme.'_version'] = array(
    '#type' => 'hidden',
    '#default' => '1.1',
  );

  // Get the current theme
  $themes = lim_get_theme_base_themes($base_theme);

  foreach ($themes as $theme) {
    $files = lim_directory_files_list('includes/forms', 'theme', $theme, 'inc');

    if(is_array($files)) {

      $form_files[$theme] = array_merge($form_files, $files);
      $weight = - count($form_files[$theme]);

      foreach ($files as $element) {
        $name = $element->name;
        $callback_name = $theme . '_' . $name . '_theme_settings_form';

        if (function_exists($callback_name)) {

          $element_form = call_user_func($callback_name, $form, $form_state);

          if (!empty($element_form)) {
            $weight++;
            $form[$name] = [
              '#type' => 'vertical_tabs',
              '#prefix' => '<h2><small>' . t('@name Settings', ['@name' => str_replace('_', '', ucwords($name, '_'))]) . '</small></h2>',
              '#weight' => $weight,
              '#tree' => TRUE,
              '#description' => t('These settings are per theme. Delete a value to use the default.'),
            ];

            $form[$name] = array_merge($form[$name], $element_form);

            // Include custom form validation and submit functions
            lim_form_system_theme_settings_attach_validate($form, $form_state, $callback_name, $element->uri);
            lim_form_system_theme_settings_attach_submit($form, $form_state, $callback_name, $element->uri);
          }
        }
      }
    }
  }
}

/**
 * @param $base_callback
 * @param $form
 * @param $form_state
 */
function lim_form_system_theme_settings_attach_validate(&$form, &$form_state, $base_callback, $file){
  $callback = $base_callback. '_validate';

  if(function_exists($callback)) {

    if(!in_array($file, $form_state['build_info']['files'])) {
      $form_state['build_info']['files'][] = $file;
    }

    $form['#validate'][] = $callback;
  }
}

/**
 * @param $base_callback
 * @param $form
 * @param $form_state
 */
function lim_form_system_theme_settings_attach_submit(&$form, &$form_state, $base_callback, $file){
  $callback = $base_callback. '_submit';

  if(function_exists($callback)) {

    if(!in_array($file, $form_state['build_info']['files'])) {
      $form_state['build_info']['files'][] = $file;
    }

    $form['#submit'][] = $callback;
  }

}