<?php

$hideContextMenu = true;
global $s;
if (!empty($_GET['class_name'])) {
 $class_names = $_GET['class_name'];
} else {
 $class_names[] = 'path';
 include_once("includes/functions/loader.inc");
 $path = new path();
 $all_search_paths = $path->findAll_searchPaths();
 $search_result_statement = "";
 $search_result_statement .= "<table class=\"first_table normal\"><thead><tr>";
 $search_result_statement .= '<th> Module </th>';
 $search_result_statement .= '<th> Search Details </th>';
 $search_result_statement .='</tr></thead>';
 If (!empty($all_search_paths)) {
	$search_result_statement .= '<tbody>';
	foreach ($all_search_paths as $key => $module_group) {
	 $search_result_statement .= ' <tr class="major_row"><td>' . $key . '</td><td><table class="second">';
	 foreach ($module_group as $paths) {
		$search_result_statement .='<tr class="minor_row">';
		$search_result_statement .='<td>' . $paths->name . '</td>';
		$search_result_statement .='<td>' . $paths->description . '</td>';
		$search_result_statement .='<td><a href="' . HOME_URL . $paths->path_link . '">' . HOME_URL . $paths->path_link . '</a></td>';
		$search_result_statement .='</tr>';
	 }
	 $search_result_statement .='</table></td></tr>';
	}
	$search_result_statement .='</tbody>';
 }
 $search_result_statement .='</table>';
 require_once(INC_BASICS . DS . "search_page.inc");
}
if (!empty($class_names)) {
 include_once("includes/functions/loader.inc");

 if (empty($access_level) || ($access_level < 2 )) {
	access_denied();
	return;
 }
// $search_form = search::x_search_form($class, 'search', 'main_search', $option_list);
// $search = new search();
 if (property_exists($$class, 'option_lists')) {
	$s->option_lists = $$class->option_lists;
 }
 $s->setProperty('_search_order_by', filter_input(INPUT_GET, 'search_order_by'));
 $s->setProperty('_search_asc_desc', filter_input(INPUT_GET, 'search_asc_desc'));
 $s->setProperty('_per_page', filter_input(INPUT_GET, 'per_page'));
 $s->setProperty('_searching_class', $class);
 if (!empty($existing_search)) {
	foreach ($existing_search as $sk => $sv) {
	 if (array_search($sv, $$class->initial_search) == false) {
		array_push($$class->initial_search, $sv);
	 }
	}
 }
 $s->setProperty('_initial_search_array', $$class->initial_search);
 if (property_exists($$class, 'search_groupBy')) {
	$s->setProperty('_group_by', $$class->search_groupBy);
 }
 if (property_exists($$class, 'search_functions')) {
	$s->setProperty('_search_functions', $$class->search_functions);
 }
 $search_form = $search->search_form($$class);

 require_once(INC_BASICS . DS . "search_page.inc");
}
?>

