<?php

/**
 * @file
 * All Preprocess functions for templates and theme fucntions.
 * If you need to add or modify preprocess functions do it in your sub-theme.
 */

/**
 * Preprocess variables for all templates.
 */
function lim_preprocess(&$vars) {}

/**
 * Preprocess variables for html.tpl.php
 */
function lim_preprocess_html(&$vars) {
  global $theme_key, $language;

  $path = drupal_get_path_alias();
  $aliases = explode('/', $path);
  foreach($aliases as $alias) {
    $vars['classes_array'][] = drupal_clean_css_identifier($alias);
  }

  // Set variable for the base path
  $vars['base_path'] = base_path();
}

/**
 * Preprocess variables for page.tpl.php
 */
function lim_preprocess_page(&$vars) {
  // Remove the 'No front page content has been created yet.' message.
  unset($vars['page']['content']['system_main']['default_message']);
  // HACK: Use custom 403 and 404 pages
  if(strpos(drupal_get_http_header("status"), '403 Forbidden') !== FALSE) {
    $vars['theme_hook_suggestions'][] = "page__403";
  }
  if (strpos(drupal_get_http_header("status"), '404 Not Found') !== FALSE) {
    $vars['theme_hook_suggestions'][] = "page__404";
  }

}

/**
 * Preprocess variables for region.tpl.php
 */
function lim_preprocess_region(&$vars) {}

/**
 * Preprocess variables for block.tpl.php
 */
function lim_preprocess_block(&$vars) {}

/**
 * Preprocess variables for field.tpl.php
 */
function lim_preprocess_field(&$vars) {}

/**
 * Preprocess variables for node.tpl.php
 */
function lim_preprocess_node(&$vars) {}

/**
 * Preprocess variables for comment.tpl.php
 */
function lim_preprocess_comment(&$vars) {}

/**
 * Preprocess variables for the search block form.
 */
function lim_preprocess_search_block_form(&$vars) {
  // Changes the search form to use the "search" input element attribute (HTML5)
  // We have to replace the string because FAPI don't know what type=search is, i.e.
  // no way we can do this in a form alter hook.
  $vars['search_form'] = str_replace('type="text"', 'type="search"', $vars['search_form']);
}

/**
 * Preprocess variables for aggregator-item.tpl.php
 */
function lim_preprocess_aggregator_item(&$vars) {}

/**
 * Override or insert variables into the fieldset template.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 */
function lim_preprocess_fieldset(&$vars) {}

/**
 * Preprocess variables for theme_image()
 */
function lim_preprocess_image(&$vars) {}

/**
 * Preprocess variables for maintenance-page.tpl.php
 */
function lim_preprocess_maintenance_page(&$vars) {}

/**
 * Preprocess variables for user-profile.tpl.php
 */
function lim_preprocess_user_profile(&$vars) {
  $vars['classes_array'][] = 'profile';
}

/**
 * Preprocess variables for breadcrumbs
 */
function lim_preprocess_breadcrumb(&$vars) {}

/**
 * Pre-processes variables for the "button" theme hook.
 *
 * See theme function for list of available variables.
 *
 * @see bootstrap_button()
 * @see theme_button()
 *
 * @ingroup theme_preprocess
 */
function lim_preprocess_button(&$vars) {
  $element = &$vars['element'];

  // Drupal buttons should be of type 'submit'.
  // @see https://www.drupal.org/node/2540452
  $element['#attributes']['type'] = 'submit';

  // Set the element's other attributes.
  element_set_attributes($element, array('id', 'name', 'value'));

  // Add the base Bootstrap button class.
  $element['#attributes']['class'][] = 'btn';

  // Add button size, if necessary.
  if ($size = bootstrap_setting('button_size')) {
    $element['#attributes']['class'][] = $size;
  }

  // Colorize button.
  _bootstrap_colorize_button($element);

  // Iconize button.
  _bootstrap_iconize_button($element);

  // Add in the button type class.
  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];

  // Ensure that all classes are unique, no need for duplicates.
  $element['#attributes']['class'] = array_unique($element['#attributes']['class']);
}


function lim_preprocess_views_exposed_form(&$vars) {

}