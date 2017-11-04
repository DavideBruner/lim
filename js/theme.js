(function($, Drupal) {

  // check if datepicker exist
  function datepicker_exist() {
    exist = false;
    if($('.datepicker').length > 0){
      exist = true;
    }
    return exist;
  }

  // Replace character
  function replaceChar(char) {
    var map =  {'d':'dd','D':'dd','m':'mm','M':'mm','y':'yyyy','Y':'yyyy'};
    if(typeof map[char] !== 'undefined'){
      return map[char];
    }
    return char;

  }
  Drupal.behaviors.ur = {
    attach: function(context, settings) {
      // Init datepicker.

      if(datepicker_exist()){
        $.each($('.datepicker'),function () {

          // Get Id
          id = $(this).attr('id');
          // Get Format
          format = $(this).attr('date-format-date');

          // split format
          format = format.split(' - ');

          // only date
          new_format='';

          // Replace with jquery format date character
          for (var x = 0; x < format[0].length; x++) {
            currentChar = format[0].charAt(x);
            new_format += replaceChar(currentChar);
          }

          //@fixme see the documentation at : http://amsul.ca/pickadate.js/date/
          // Initialize picker
          $(this).pickadate({
            monthsFull: ['Gennaio', 'Febbraio', 'Marzo', 'Aprile', 'Maggio', 'Giugno', 'Luglio', 'Agosto', 'Settembre', 'Ottobre', 'Novembre', 'Dicembre'],
            weekdaysShort: ['Dom', 'Lun', 'Mar', 'Mer', 'Gio', 'Ven', 'Sab'],
            today: 'Oggi',
            clear: 'Cancella',
            'format':new_format
          });
        })
      }
    }
  },
    Drupal.behaviors.fileUpload = {
      attach: function(context, settings) {
        var items = $('.js-upload-file');
        if(items.length > 0 ){
          $.each(items, function(){

            // Get field name.
            field_name = $(this).attr('data-item');

            // Get field value.
            field_value = $('input[name="'+field_name+'"]').val();


            // If field value is empty or undefined, disable button upload.
            if(typeof field_value !== 'undefined' || field_value === ''){

              // add class disable to upload button.
              $(this).parent().find('.input-group-btn button').attr('disabled',true);
            }
            // At change of this input, place name file to fake input area.
            $('input[name="'+field_name+'"]').change(function () {

              // Get file name.
              filename = $(this)[0].files.length ? $(this)[0].files[0].name : Drupal.t("Carica File");

              // Place file name to div.
              $(this).parent().find('.js-filename').text(filename);

              // Enable disable upload button.
              StringT = Drupal.t("Carica Fiel");
              if(filename == StringT){
                $(this).parent().find('.input-group-btn button').attr('disabled',true);
              }else {
                $(this).parent().find('.input-group-btn button').attr('disabled',false);
              }
            })
          });
        }



        // Fake button trigger click to real input type file by fieldname.
        $('p.js-button-trigger-file-upload').once(function(){
          $(this).click(function () {
            field_name =  $(this).closest('ul').attr('data-item');

            $(this).closest('ul').parent().find('input[name="' + field_name + '"]').click();

          })
        })

      }
    }
})(jQuery, Drupal);