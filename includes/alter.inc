<?php

/**
 * @file
 * General alters.
 */

/**
 * hook_html_head_alter()
 */
function lim_html_head_alter(&$head_elements) {
  global $theme_key;
  $theme_name = $theme_key;
  $path_to_theme = drupal_get_path('theme', $theme_name);
  $default_icon_path = $path_to_theme . '/favicon';

  /** Meta */
  $head_elements['meta'] = [
    // Viewport
    'viewport' => [
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'viewport',
        'content' => check_plain(lim_get_theme_setting('viewport')),
      ),
      '#weight' => 1,
    ],
    // Theme Color
    'theme_color' => [
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'theme-color',
        'content' => check_plain(lim_get_theme_setting('theme_color')),
      ),
      '#weight' => 100,
    ],
    '#tree' => TRUE
  ];

}

/**
 * Implements hook_element_info_alter().
 */
function lim_element_info_alter(&$type) {}


/**
 * hook_page_alter()
 */
function lim_page_alter(&$page) {}

/**
 * hook_js_alter()
 */
function lim_js_alter(&$javascript) {
  global $theme_key;
}

/**
 * hook_css_alter()
 */
function lim_css_alter(&$css) {
  global $theme_key;
}

/**
 * Implements hook_libraries_info_alter().
 */
function lim_libraries_info_alter(&$libraries) {
  //dpm($libraries);
}


/**
 * Implements hook_form_FORM_ID_alter().
 */
function lim_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
  $info = $form['#info'];
  /* Use the filter label as placeholder attributes of all filters */
  foreach ($info as $filter_name => $filter) {

    $placeholder = $filter['label'];
    $field_name = $filter['value'];
    // Hide the label based on field type
    switch ($form[$field_name]['#type']) {
      case 'select' :
        if(isset($form[$field_name]['#options']['All'])) {
          $label = '- '. t($placeholder) . ' -';
          $form[$field_name]['#options']['All'] = $label;
          unset($form['#info'][$filter_name]['label']);
        }
        break;
      default :
        $form[$field_name]['#attributes'] = ['placeholder' => [t($placeholder)]];
        unset($form['#info'][$filter_name]['label']);
        break;
    }
  }
  /* Define the search icon as submit value */
  $icon = _bootstrap_icon('search');
  $form['submit']['#icon'] = $icon;
  unset($form['submit']['#value']);
}