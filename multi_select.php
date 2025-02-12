<?php
set_time_limit(300);
/* $header_id_name and $header_id_value is used only in case of AP/PO matching
 * Serach class is PO and action class is AP Line but to save AP line, AP Header Id is required and teh value
 * is stored in $header_id_value
 * 
 */
$hideContextMenu = true;
$hideBlock = true;
$show_block = 0;
if ((!empty($_GET['show_block'])) && ($_GET['show_block'] == 1)) {
 $hideBlock = false;
 $show_block = 1;
}
if (!empty($_GET['class_name'])) {
 $class_names = $_GET['class_name'];
 $pageTitle = " $class_names - Select value of $class_names ";
} else {
 $path_access = -1;
}
if (!empty($class_names)) {
 include_once("includes/functions/loader.inc");
  if (empty($access_level) || ($access_level < 3 )) {
	access_denied();
	return;
 }
 $action_message = !(empty($_GET['action'])) ? $_GET['action'] : null;
 $hidden_field_a = [];

 if (!empty($_GET['action_class_name'])) {
	$action_class = $_GET['action_class_name'];
 } else {
	$action_class = $_GET['class_name'];
 }

 if (!empty($action_class)) {
	$action_class_i = new $action_class();

	if (method_exists($action_class_i, 'multi_select_verification')) {
	 $action_class_i->multi_select_verification($error_msg);
	}

	IF (property_exists($action_class_i, 'multi_search_primary_column')) {
	 $header_id_name = $action_class_i::$multi_search_primary_column;
	} else {
	 $header_id_name = null;
	}
	$header_id_value = null;

	if (!empty($_GET[$header_id_name])) {
	 $header_id_value = $_GET[$header_id_name];
	}
	if (method_exists($action_class, 'multi_select_input_fields')) {
	 $multi_selct_input_fields = $action_class_i->multi_select_input_fields();
	}
	if (method_exists($action_class, 'multi_select_hidden_fields')) {
	 $hidden_field_names = $action_class_i->multi_select_hidden_fields();
	 if (!empty($_GET)) {
		foreach ($hidden_field_names as $hiden_field_name) {
		 if (!empty($_GET[$hiden_field_name])) {
			$hidden_field_a[$hiden_field_name] = $_GET[$hiden_field_name];
		 } else {
			$hidden_field_a[$hiden_field_name] = null;
		 }
		}
	 }
	}
 } else {
	$multi_selct_input_fields = null;
	$hidden_field_names = null;
 }
// 
// pa($hidden_field_names);
//// pa($multi_selct_input_fields);
//// pa($hidden_field_a);

 $search = new search();
 $search->setProperty('_search_order_by', filter_input(INPUT_GET, 'search_order_by'));
 $search->setProperty('_search_asc_desc', filter_input(INPUT_GET, 'search_asc_desc'));
 $search->setProperty('_per_page', filter_input(INPUT_GET, 'per_page'));
 $search->setProperty('_searching_class', $class);
 $search->setProperty('_form_post_link', 'multi_select');
 $search->setProperty('_initial_search_array', $$class->initial_search);
 $search->setProperty('_hidden_fields', $hidden_field_a);
 $search->setProperty('_search_mode', $mode);
 $search->setProperty('_show_block', $show_block);
  if (property_exists($$class, 'search_functions')) {
	$s->setProperty('_search_functions', $$class->search_functions);
 }
 $search_form = $search->search_form($$class);

$hidden_field_stmt = $search->hidden_fields();

 if (!empty($pagination)) {
	$pagination->setProperty('_path', 'multi_select');
	$pagination_statement = $pagination->show_pagination();
 }
}
?>

<?php 	If(property_exists($action_class_i, 'js_fileName')){?>
<script src="<?php echo HOME_URL.$action_class_i::$js_fileName; ?>"></script>	 
<?php } ?>

<?php
if (property_exists($$class, 'multi_select_template_path')) {
 require_once($class::$multi_select_template_path);
} else {
 require_once(INC_BASICS . DS . "multi_select_page.inc");
}
?>