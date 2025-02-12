function setValFromSelectPage(supplier_id, supplier_number, supplier_name,
address_id, address_name, address, country, postal_code) {
 this.supplier_id = supplier_id;
 this.supplier_number = supplier_number;
 this.supplier_name = supplier_name;
  this.address_id = address_id;
 this.address_name = address_name;
 this.address = address;
 this.country = country;
 this.postal_code = postal_code;
}

setValFromSelectPage.prototype.setVal = function() {
 var supplier_id = this.supplier_id;
 var supplier_number = this.supplier_number;
 var supplier_name = this.supplier_name;
  var address_id = this.address_id;
 var address_name = this.address_name;
 var address = this.address;
 var country = this.country;
 var postal_code = this.postal_code;
 var addressPopupDivClass = '.' + localStorage.getItem("addressPopupDivClass");
 addressPopupDivClass = addressPopupDivClass.replace(/\s+/g, '.');
 if (address_id) {
	$('#content').find(addressPopupDivClass).find('.address_id').val(address_id);
 }
 if (address_name) {
	$('#content').find(addressPopupDivClass).find('.address_name').val(address_name);
 }
 if (address) {
	$('#content').find(addressPopupDivClass).find('.address').val(address);
 }
 if (country) {
	$('#content').find(addressPopupDivClass).find('.country').val(country);
 }
 if (postal_code) {
	$('#content').find(addressPopupDivClass).find('.postal_code').val(postal_code);
 }


 if (supplier_id) {
	$("#supplier_id").val(supplier_id);
 }
 if (supplier_number) {
	$("#supplier_number").val(supplier_number);
 }
 if (supplier_name) {
	$("#supplier_name").val(supplier_name);
 }

};


$(document).ready(function() {
//selecting supplier
 $(".supplier_id_popup").click(function() {
	void window.open('select.php?class_name=supplier', '_blank',
					'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
	return false;
 });

 //Get the supplier_id on refresh button click
 $('a.show.supplier_id').click(function() {
	var supplier_id = $('#supplier_id').val();
	$(this).attr('href', modepath() + 'supplier_id=' + supplier_id);

 });

 //Popup for selecting address 
 $(".address_popup").click(function() {
	var addressPopupDivClass = $(this).closest('div').prop('class');
	localStorage.setItem("addressPopupDivClass", addressPopupDivClass);
	void window.open('select.php?class_name=address', '_blank',
					'width=1000,height=800,TOOLBAR=no,MENUBAR=no,SCROLLBARS=yes,RESIZABLE=yes,LOCATION=no,DIRECTORIES=no,STATUS=no');
	return false;
 });


 $('a.show.supplier_number').click(function() {
	var supplier_number = $('#supplier_number').val();
	if ($('#org_id').val().length > 0) {
	 var org_id = $('#org_id').val();
	 $(this).attr('href', modepath() + 'supplier_number=' + supplier_number + '&org_id=' + org_id);
	} else {
	 alert("Query Error!!! \n Select the query mode by pressing Ctrl + Q \n Select the organization name");
	}
 });

 $('a.show.supplier_site_id').click(function() {
	var supplier_id = $('#supplier_id').val();
	var supplier_site_id = $('#supplier_site_id').val();
	$(this).attr('href', modepath() + 'supplier_id=' + supplier_id + '&supplier_site_id=' + supplier_site_id);
 });

 $("#supplier_site_name").on("change", function() {
	if ($(this).val() == 'newentry') {
	 if (confirm("Do you want to create a new supplier site?")) {
		$(this).replaceWith('<input id="supplier_site_name" class="textfield supplier_site_name" type="text" size="25" maxlength="50" name="supplier_site_name[]">');
		$(".show.supplier_site_id").hide();
		$("#supplier_site_id").val("");
		$("#supplier_site_number").val("");
	 }

	}
 });


//context menu
 var classContextMenu = new contextMenuMain();
 classContextMenu.docHedaderId = 'gl_journal_header_id';
 classContextMenu.docLineId = 'gl_journal_line_id';
 classContextMenu.btn1DivId = 'gl_journal_header';
 classContextMenu.btn2DivId = 'form_line';
 classContextMenu.trClass = 'gl_journal_line';
 classContextMenu.tbodyClass = 'form_data_line_tbody';
 classContextMenu.noOfTabbs = 3;
// classContextMenu.contextMenu();

//FILE attachment
 var fu = new fileUploadMain();
 fu.json_url = 'extensions/file/upload.php';
 fu.module_name = 'ap';
 fu.class_name = 'supplier';
 fu.document_type = 'supplier';
// fu.directory = 'ap/supplier';
 fu.fileUpload();


//Save record
 var classSave = new saveMainClass();
 classSave.json_url = 'form.php?class_name=supplier';
 classSave.form_header_id = 'supplier_header';
 classSave.primary_column_id = 'supplier_id';
 classSave.line_key_field = 'supplier_site_name';
 classSave.single_line = true;
 classSave.form_line_id = 'supplier_site';
 classSave.enable_select = true;
 if (!$('#supplier_id').val()) {
	classSave.savingOnlyHeader = true;
 } else {
	classSave.savingOnlyHeader = false;
 }
 classSave.headerClassName = 'supplier';
 classSave.lineClassName = 'supplier_site';
 classSave.saveMain();
//save('json.supplier.php', '#supplier', '', 'supplier', '#supplier_id', "#supplier_site");

//delete line
 deleteData('json.supplier.php');

});
