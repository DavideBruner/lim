<?php

/**
 * @file
 * Custom theme functions and theme function overrides.
 *
 * If you need to add or modify theme functions do it in your sub-theme.
 */

/**
 * Implements hook_theme()
 *
 * @param $existing
 * @param $type
 * @param $theme
 * @param $path
 *
 * @see http://api.drupal.org/api/drupal/modules!system!system.api.php/function/hook_theme/7
 */
/* function lim_theme($existing, $type, $theme, $path) {} */

/**
 * Returns HTML for a breadcrumb trail.
 *
 * lim renders breadcrumbs as an ordered list (<ol>...</ol>), wrapping
 * crumbs in li elements and the seperators in span elements. Additionally .crumb,
 * .crumb-first and .crumb-last classes are printed on the li elements. We also
 * remove some silly breadcrumbs from various pages.
 *
 * @param $vars
 *   An associative array containing:
 *   - breadcrumb: An array containing the breadcrumb links.
 */
/* function lim_breadcrumb($vars) {} */

/**
 * Returns HTML for status and/or error messages, grouped by type.
 *
 * An invisible heading identifies the messages for assistive technology.
 * Sighted users see a colored box. See http://www.w3.org/TR/WCAG-TECHS/H69.html
 * for info.
 *
 * @param array $variables
 *   An associative array containing:
 *   - display: (optional) Set to 'status' or 'error' to display only messages
 *     of that type.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_status_messages()
 *
 * @ingroup theme_functions
 */
function lim_status_messages(&$variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
    'info' => t('Informative message'),
  );

  // Map Drupal message types to their corresponding Bootstrap classes.
  // @see http://twitter.github.com/bootstrap/components.html#alerts
  $status_class = array(
    'status' => 'success',
    'error' => 'danger',
    'warning' => 'warning',
    // Not supported, but in theory a module could send any type of message.
    // @see drupal_set_message()
    // @see theme_status_messages()
    'info' => 'info',
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    $class = (isset($status_class[$type])) ? ' alert-' . $status_class[$type] : '';
    $output .= "<div class=\"alert alert-block$class messages $type\">\n";
    $output .= "  <a class=\"close\" data-dismiss=\"alert\" href=\"#\">&times;</a>\n";

    if (!empty($status_heading[$type])) {
      $output .= '<h4 class="element-invisible">' . $status_heading[$type] . "</h4>\n";
    }

    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }

    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Returns HTML for a list or nested list of items.
 *
 * lim overrides this in order to insert extra classes into list
 * items, including first, last and odd/even zebra classes.
 *
 * @param $vars
 *   An associative array containing:
 *   - items: An array of items to be displayed in the list. If an item is a
 *     string, then it is used as is. If an item is an array, then the "data"
 *     element of the array is used as the contents of the list item. If an item
 *     is an array with a "children" element, those children are displayed in a
 *     nested list. All other elements are treated as attributes of the list
 *     item element.
 *   - title: The title of the list.
 *   - type: The type of list to return (e.g. "ul", "ol").
 *   - attributes: The attributes applied to the list element.
 */
/* function lim_item_list($vars) {} */

/**
 * Returns HTML for a wrapper for a menu sub-tree.
 *
 * lim overrides this to insert the clearfix class.
 *
 * @param $vars
 *   An associative array containing:
 *   - tree: An HTML string containing the tree's items.
 *
 * @see template_preprocess_menu_tree()
 */
/* function lim_menu_tree($vars) {} */

/**
 * Returns HTML for a menu link and submenu.
 *
 * lim overrides this to insert extra classes including a depth
 * class and a menu id class. It can also wrap menu items in span elements.
 *
 * @param $vars
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 */
/* function lim_menu_link(array $vars) {} */

/**
 * Returns HTML for a set of links.
 *
 * @param $vars
 *   An associative array containing:
 *   - links: An associative array of links to be themed. The key for each link
 *     is used as its CSS class. Each link should be itself an array, with the
 *     following elements:
 *     - title: The link text.
 *     - href: The link URL. If omitted, the 'title' is shown as a plain text
 *       item in the links list.
 *     - html: (optional) Whether or not 'title' is HTML. If set, the title
 *       will not be passed through check_plain().
 *     - attributes: (optional) Attributes for the anchor, or for the <span> tag
 *       used in its place if no 'href' is supplied. If element 'class' is
 *       included, it must be an array of one or more class names.
 *     If the 'href' element is supplied, the entire link array is passed to l()
 *     as its $options parameter.
 *   - attributes: A keyed array of attributes for the UL containing the
 *     list of links.
 *   - heading: (optional) A heading to precede the links. May be an associative
 *     array or a string. If it's an array, it can have the following elements:
 *     - text: The heading text.
 *     - level: The heading level (e.g. 'h2', 'h3').
 *     - class: (optional) An array of the CSS classes for the heading.
 *     When using a string it will be used as the text of the heading and the
 *     level will default to 'h2'. Headings should be used on navigation menus
 *     and any list of links that consistently appears on multiple pages. To
 *     make the heading invisible use the 'element-invisible' CSS class. Do not
 *     use 'display:none', which removes it from screen-readers and assistive
 *     technology. Headings allow screen-reader and keyboard only users to
 *     navigate to or skip the links. See
 *     http://juicystudio.com/article/screen-readers-display-none.php and
 *     http://www.w3.org/TR/WCAG-TECHS/H42.html for more information.
 */
/* function lim_links($vars) {} */

/**
 * Returns HTML for a field.
 *
 * lim overrides this in order to better support HTML5 by setting the
 * wrapper as section or div element depending on whether a title is used or not.
 * Fields have no title, instead it treats the field lable as if it were a title
 * and wraps it in h2 elements.
 *
 * This is the default theme implementation to display the value of a field.
 * Theme developers who are comfortable with overriding theme functions may do
 * so in order to customize this markup. This function can be overridden with
 * varying levels of specificity. For example, for a field named 'body'
 * displayed on the 'article' content type, any of the following functions will
 * override this default implementation. The first of these functions that
 * exists is used:
 * - THEMENAME_field__body__article()
 * - THEMENAME_field__article()
 * - THEMENAME_field__body()
 * - THEMENAME_field()
 *
 * Theme developers who prefer to customize templates instead of overriding
 * functions may copy the "field.tpl.php" from the "modules/field/theme" folder
 * of the Drupal installation to somewhere within the theme's folder and
 * customize it, just like customizing other Drupal templates such as
 * page.tpl.php or node.tpl.php. However, it takes longer for the server to
 * process templates than to call a function, so for websites with many fields
 * displayed on a page, this can result in a noticeable slowdown of the website.
 * For these websites, developers are discouraged from placing a field.tpl.php
 * file into the theme's folder, but may customize templates for specific
 * fields. For example, for a field named 'body' displayed on the 'article'
 * content type, any of the following templates will override this default
 * implementation. The first of these templates that exists is used:
 * - field--body--article.tpl.php
 * - field--article.tpl.php
 * - field--body.tpl.php
 * - field.tpl.php
 * So, if the body field on the article content type needs customization, a
 * field--body--article.tpl.php file can be added within the theme's folder.
 * Because it's a template, it will result in slightly more time needed to
 * display that field, but it will not impact other fields, and therefore,
 * is unlikely to cause a noticeable change in website performance. A very rough
 * guideline is that if a page is being displayed with more than 100 fields and
 * they are all themed with a template instead of a function, it can add up to
 * 5% to the time it takes to display that page. This is a guideline only and
 * the exact performance impact depends on the server configuration and the
 * details of the website.
 *
 * @param $vars
 *   An associative array containing:
 *   - label_hidden: A boolean indicating to show or hide the field label.
 *   - title_attributes: A string containing the attributes for the title.
 *   - label: The label for the field.
 *   - content_attributes: A string containing the attributes for the content's
 *     div.
 *   - items: An array of field items.
 *   - item_attributes: An array of attributes for each item.
 *   - classes: A string containing the classes for the wrapping div.
 *   - attributes: A string containing the attributes for the wrapping div.
 *
 * @see template_preprocess_field()
 * @see template_process_field()
 * @see field.tpl.php
 */
/* function lim_field($vars) {} */

/**
 * Returns HTML for a taxonomy field.
 *
 * Output taxonomy term fields as unordered lists.
 */
/* function lim_field__taxonomy_term_reference($vars) {} */

/**
 * Returns HTML for an image field.
 *
 * Output image fields as figure with figcaption for captioning.
 */
//function lim_field__image($vars) {}

/**
 * Returns HTML for a form.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #action, #method, #attributes, #children
 *
 * @ingroup themeable
 */
/* function lim_form($variables) {} */

/**
 * Returns HTML for a form element.
 *
 * Each form element is wrapped in a DIV container having the following CSS
 * classes:
 * - form-item: Generic for all form elements.
 * - form-type-#type: The internal element #type.
 * - form-item-#name: The internal form element #name (usually derived from the
 *   $form structure and set via form_builder()).
 * - form-disabled: Only set if the form element is #disabled.
 *
 * In addition to the element itself, the DIV contains a label for the element
 * based on the optional #title_display property, and an optional #description.
 *
 * The optional #title_display property can have these values:
 * - before: The label is output before the element. This is the default.
 *   The label includes the #title and the required marker, if #required.
 * - after: The label is output after the element. For example, this is used
 *   for radio and checkbox #type elements as set in system_element_info().
 *   If the #title is empty but the field is #required, the label will
 *   contain only the required marker.
 * - invisible: Labels are critical for screen readers to enable them to
 *   properly navigate through forms but can be visually distracting. This
 *   property hides the label for everyone except screen readers.
 * - attribute: Set the title attribute on the element to create a tooltip
 *   but output no label element. This is supported only for checkboxes
 *   and radios in form_pre_render_conditional_form_element(). It is used
 *   where a visual label is not needed, such as a table of checkboxes where
 *   the row and column provide the context. The tooltip will include the
 *   title and required marker.
 *
 * If the #title property is not set, then the label and any required marker
 * will not be output, regardless of the #title_display or #required values.
 * This can be useful in cases such as the password_confirm element, which
 * creates children elements that have their own labels and required markers,
 * but the parent element should have neither. Use this carefully because a
 * field without an associated label can cause accessibility challenges.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #title_display, #description, #id, #required,
 *     #children, #type, #name.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_form_element()
 *
 * @ingroup theme_functions
 */
/* function lim_form_element(&$variables) {} */

/**
 * Returns HTML for a hidden form element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #name, #value, #attributes.
 *
 * @ingroup themeable
 */
/* function lim_hidden($variables) {} */

/**
 * Returns HTML for a form element label and required marker.
 *
 * Form element labels include the #title and a #required marker. The label is
 * associated with the element itself by the element #id. Labels may appear
 * before or after elements, depending on theme_form_element() and
 * #title_display.
 *
 * This function will not be called for elements with no labels, depending on
 * #title_display. For elements that have an empty #title and are not required,
 * this function will output no label (''). For required elements that have an
 * empty #title, this will output the required marker alone within the label.
 * The label will use the #id to associate the marker with the field that is
 * required. That is especially important for screenreader users to know
 * which field is required.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #required, #title, #id, #value, #description.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_form_element_label()
 *
 * @ingroup theme_functions
 */
/* function lim_form_element_label(&$variables) {} */

/**
 * Returns HTML for a button form element.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #attributes, #button_type, #name, #value.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_button()
 *
 * @ingroup theme_functions
 */
/* function lim_button(&$variables) {} */

/**
 * Returns HTML for a textfield form element.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #description, #size, #maxlength,
 *     #required, #attributes, #autocomplete_path.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_textfield()
 *
 * @ingroup theme_functions
 */
/* function lim_textfield($variables) {} */

/**
 * Returns HTML for a textarea form element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #description, #rows, #cols, #required,
 *     #attributes
 *
 * @ingroup themeable
 */
/* function lim_textarea($variables) {} */

/**
 * Returns HTML for a select form element.
 *
 * It is possible to group options together; to do this, change the format of
 * $options to an associative array in which the keys are group labels, and the
 * values are associative arrays in the normal $options format.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #options, #description, #extra,
 *     #multiple, #required, #name, #attributes, #size.
 *
 * @ingroup themeable
 */
/* function lim_select($variables) {} */

/**
 * Returns HTML for a password form element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #description, #size, #maxlength,
 *     #required, #attributes.
 *
 * @ingroup themeable
 */
/* function lim_password($variables) {} */

/**
 * Returns HTML for a file upload form element.
 *
 * For assistance with handling the uploaded file correctly, see the API
 * provided by file.inc.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #name, #size, #description, #required,
 *     #attributes.
 *
 * @ingroup themeable
 */
/* function lim_file(&$variables) {} */

/**
 * Returns HTML for a query pager.
 *
 * Menu callbacks that display paged query results should call theme('pager') to
 * retrieve a pager control so that users can view other results. Format a list
 * of nearby pages with additional query results.
 *
 * @param $variables
 *   An associative array containing:
 *   - tags: An array of labels for the controls in the pager.
 *   - element: An optional integer to distinguish between multiple pagers on
 *     one page.
 *   - parameters: An associative array of query string parameters to append to
 *     the pager links.
 *   - quantity: The number of pages in the list.
 *
 * @ingroup themeable
 */
/* function lim_pager($variables) {} */

/**
 * Returns HTML for a progress bar.
 *
 * Note that the core Batch API uses this only for non-JavaScript batch jobs.
 *
 * @param $variables
 *   An associative array containing:
 *   - percent: The percentage of the progress.
 *   - message: A string containing information to be displayed.
 */
/* function lim_progress_bar($variables) {} */