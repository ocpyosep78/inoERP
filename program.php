<?php
if (!empty($_POST)) {
 include_once ('includes/basics/basics.inc');
 $postArray = get_postArray_From_jqSearializedArray($_POST['headerData']);
  if ((!empty($postArray['class_name'])) && (!empty($postArray['program_name']))) {
	$class = $postArray['class_name'][0];
	$program_name = $postArray['program_name'][0];
	$p = new sys_program();
	$p->program_name = $program_name;
	$p->class = $class;
	$p->parameters = serialize($postArray);
	$p->status = 'Initiated';
	$p->audit_trial();
	try {
	 $p->save();
	 echo "<div id='json_save_header'><div class='message'>The program is sucessfully saved; Program Id is " . $p->sys_program_id . '</div></div>';
	} catch (Exception $e) {
	 echo " Saving the program failed! " . $e->getMessage();
	 return -99;
	}
 }
 return;
}
?>
<?php

$hideContextMenu = true;
global $s;
if ((!empty($_GET['class_name'])) && (!empty($_GET['program_name']))) {
 $class_names = $_GET['class_name'];
 $program_name = $_GET['program_name'];
 $_GET['mode'] = 2;
} else {
 $class_names[] = 'path';
 include_once("includes/functions/loader.inc");
 $path = new path();
 $all_search_paths = $path->findAll_programPaths();
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
if ((!empty($class_names)) && (!empty($program_name))) {
 include_once("includes/functions/loader.inc");
 $hidden_field_a = ['program_name' => $program_name];
 $program_parameters = $program_name . '_parameters';
 $program_details_n = $program_name . '_details';
 $program_details = $$class->$program_details_n;
 $program_name = $program_details['name'];
 $s->setProperty('_searching_class', $class);
 $s->setProperty('_form_name', 'program_header');
 $search->setProperty('_hidden_fields', $hidden_field_a);
 $s->setProperty('_initial_search_array', $$class->initial_search);

 if (property_exists($$class, $program_parameters)) {
	$s->setProperty('_search_functions', $$class->$program_parameters);
 }
 $search_form = $s->program_form($$class);

 require_once(INC_BASICS . DS . "program_page.inc");
}
?>

