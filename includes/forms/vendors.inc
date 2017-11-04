<?php

$theme_path = drupal_get_path('theme', 'lim');
require_once($theme_path . '/includes/vendors.inc');       // get theme info, settings, css etc

/**
 * @param $form
 * @param $form_state
 *
 * @return array
 */
function lim_vendors_theme_settings_form($form, $form_state) {
  $form = [];
  $vendors = get_theme_vendors();

  // Create vertical tabs for vendors related settings.
  foreach ($vendors as $vendor_id => $vendor_settings) {
    // Iterate foreach vendor to display a single vendor in a fieldset
    $form['vendors'][$vendor_id] = [
      '#type' => 'fieldset',
      '#title' => t(ucwords($vendor_id)),
      '#parents' => array('vendors'),
    ];

    $form['vendors'][$vendor_id][$vendor_id . '_active'] = [
      '#weight' => -10,
      '#type' => 'checkbox',
      '#title' => t('Enable') . ' ' . ucwords($vendor_id),
      '#default_value' => lim_get_theme_setting($vendor_id . '_active'),
      '#description' => t('Use this checkbox to include !vendor libraries.', [
        '!vendor' => $vendor_id,
      ])
    ];

    $default_inc_path = 'sites/all/themes/lim/includes/vendors/'. $vendor_id . '/' .$vendor_id. '.inc';

    $form['vendors'][$vendor_id][$vendor_id . '_inc'] = [
      '#type' => 'textfield',
      '#title' => t('Include ') . ' ' . ucwords($vendor_id),
      '#default_value' => lim_get_theme_setting($vendor_id . '_inc', NULL,isset($vendor_settings['inc']) ? check_plain($vendor_settings['inc']) : $default_inc_path),
      '#description' => t('The !vendor php file to include. Use an absolute path ex. <em><b>!default</b></em> ', [
        '!vendor' => $vendor_id,
        '!default' => $default_inc_path
      ]),
      '#states'        => array(
        // Show only if placement in "content" selected
        'visible' => array(
          ':input[name="'.$vendor_id.'_active"]' => array(
            'checked' => TRUE
          ),
        ),
      ),
    ];

    $vendor_settings_form = vendor_settings_form($vendor_id, $form, $form_state);
    if(!empty($vendor_settings_form)) {
      // Associate custom form settings to the base form recursively
      $form['vendors'][$vendor_id] = array_merge_recursive($form['vendors'][$vendor_id], $vendor_settings_form[$vendor_id]);
    }

  }

  return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function lim_vendors_theme_settings_form_submit($form, $form_state) {
  $theme = reset($form_state['build_info']['args']);
  foreach (element_children($form['vendors']) as $vendor_id) {
    if(isset($form_state['input'][$vendor_id.'_inc']) && !empty($form_state['input'][$vendor_id.'_inc'])
      && $form_state['input'][$vendor_id.'_active']) {
      $file =  $form_state['input'][$vendor_id.'_inc'];
      update_vendors_settings($theme, $vendor_id, array('inc' => $file));
    }
  }
  // Rebuild the theme data.
  system_rebuild_theme_data();
  drupal_theme_rebuild();
  drupal_set_message('The theme cache has been cleared.');
}

/**
 * @param $form
 * @param $form_state
 */
function lim_vendors_theme_settings_form_validate($form, $form_state) {
  foreach (element_children($form['vendors']) as $vendor_id) {
    if(isset($form_state['input'][$vendor_id.'_inc']) && !empty($form_state['input'][$vendor_id.'_inc'])
      && $form_state['input'][$vendor_id.'_active']) {

      $file =  $form_state['input'][$vendor_id.'_inc'];
      if(!file_exists($file)) {
        form_set_error($vendor_id.'_inc',t("The file !file doesn't exist.", ['!file' => $file]));
      }
    }
  }
}

