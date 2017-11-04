<?php

/**
 * @file
 * All Process functions for templates and theme fucntions.
 *
 * If you need to add or modify process functions do it in your sub-theme.
 */

/**
 * Process variables for html.tpl.php
 */
function lim_process_html(&$vars) {
  // Flatten attributes arrays
  $vars['html_attributes'] = empty($vars['html_attributes_array']) ? '' : drupal_attributes($vars['html_attributes_array']);

  // $rdf_namespaces is kept to maintain backwards compatibility, and because we
  // only want this to print once in html.tpl.php, and not in every conditional
  // comment for IE.
  $vars['rdf_namespaces'] = empty($vars['rdf_namespaces_array']) ? '' : drupal_attributes($vars['rdf_namespaces_array']);

}

/**
 * Process variables for page.tpl.php
 */
function lim_process_page(&$vars) {
  if (isset($vars['node'])) {
    $suggestion = 'page__' . $vars['node']->type;
    array_unshift($vars['theme_hook_suggestions'], $suggestion);
  }
}

/**
 * Process variables for region.tpl.php
 */
function lim_process_region(&$vars) {}

/**
 * Process variables for block.tpl.php
 */
function lim_process_block(&$vars) {
  // Provide additional suggestions so the block__menu suggestion can be overridden easily
  $vars['theme_hook_suggestions'][] = 'block__' . $vars['block']->region . '__' . $vars['block']->module;
  $vars['theme_hook_suggestions'][] = 'block__' . $vars['block']->region . '__' . $vars['block']->delta;
}

/**
 * Process variables for node.tpl.php
 */
function lim_process_node(&$vars) {
}

/**
 * Process variables for comment.tpl.php
 */
function lim_process_comment(&$vars) {}

/**
 * Process variables for maintenance-page.tpl.php
 */
function lim_process_maintenance_page(&$vars) {}

/**
 * Process variables for user-profile.tpl.php
 */
function lim_process_user_profile(&$vars) {}
