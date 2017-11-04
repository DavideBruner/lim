<?php

function lim_less_theme_settings_form($form, $form_state) {
  $less_settings = lim_get_theme_setting('less');
  // Flush less caches to rebuild variables array
  //less_flush_caches();
  //dpm(less_get_settings('psp'));

}