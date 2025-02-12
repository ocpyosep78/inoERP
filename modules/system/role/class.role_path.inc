<?php

class role_path extends dbObject {

 protected static $table_name = "role_path";
//  data base variables as stored database column name
 public static $field_array = [
		 "role_path_id",
		 "role_id",
		 "path_id",
		 "created_by",
		 "creation_date",
		 "last_update_by",
		 "last_update_date"
 ];
 public static $initial_search_array = [
		 "role_path_id",
		 "role_id",
		 "path_id"
 ];
//variables used for showing data
 public static $checkbox_array = [
 ];
 public static $column_array = [
		 "role_path_id",
		 "role_id",
		 "path_id"
 ];
 public static $requiredField_array = [
		 "role_id",
		 "path_id"
 ];
 public static $primary_column = "role_path_id";
 public $role_id;
 public $role_path_id;
 public $path_id;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;
 public $time;
 public $msg;

// function __construct() {
//	self::assign_role_paths();
// }

 public function assign_role_paths() {
	if (!empty($_SESSION['user_id']) && (in_array('admin', $_SESSION['user_roles']))) {
	 $paths = path::find_all();
	 $allowed_path_ids = [];
	 foreach ($paths as $path) {
		$allowed_path_ids[] = $path->path_id;
	 }
	 $_SESSION['allowed_path_ids'] = $allowed_path_ids;
	} else if (empty($_SESSION['allowed_path_ids']) &&
					(!empty($_SESSION['user_role_ids'])) &&
					(!empty($_SESSION['user_id']))) {
	 $allowed_path_ids = [];
	 $user_id = $_SESSION['user_id'];
	 $role_id_array = $_SESSION['user_role_ids'];
	 foreach ($role_id_array as $role_id) {
		$paths = self::find_by_roleId($role_id);
		foreach ($paths as $path) {
		 $allowed_path_ids[] = $path->path_id;
		}
	 }
	 $_SESSION['allowed_path_ids'] = $allowed_path_ids;
	} 
	if(empty($_SESSION['allowed_path_ids'])) {
	 $_SESSION['allowed_path_ids'] = "";
	}
	$_SESSION['allowed_path_ids_all'] = $_SESSION['allowed_path_ids'];
//	print_r($_SESSION['allowed_path_ids_all']);
	}

 public function check_path_access() {
	$url = $_SERVER['REQUEST_URI'];
	$path = path::get_path_from_url($url);
	
	if (($path == 'index.php' 
					|| $path == 'extensions/user/user_login.php' 
					|| $path == 'extensions/user/user_logout.php'
					|| $path == 'include/basics/json.basics.php')) {
	 $path_allowed = 1;
	} else {
	  $path_id = path::get_path_id_from_url($url);
//		echo "<br/>path id is $path_id";

	 if (!empty($_SESSION['allowed_path_ids'])) {
		$path_allowed = in_array($path_id, $_SESSION['allowed_path_ids']);
	 } else {
		$path_allowed = 0;
	 }
	}
//	echo "<br/>path_allowed is $path_allowed";
	return $path_allowed;
 }

 Public static function roles() {
	$option_type = option_header::find_by_name('USER_ROLES');
	$option_line = option_line::find_by_option_id($option_type->option_header_id);
	return $option_line;
 }

 public static function find_by_roleId($role_id) {
	$sql = "SELECT * FROM " . self::$table_name . " where role_id={$role_id} ";
	$result = self::find_by_sql($sql);
	return $result;
 }

 public static function role_path_all_v() {
	global $db;
	$sql = " SELECT * FROM ";
	$sql .=" role_path AS rp , option_line  AS ol";
	$sql .=" WHERE rp.role_id = ol.option_line_id ";

	$result = $db->result_array_assoc($sql);

	return $result;
 }
 
  Public static function all_roles() {
	$option_header = option_header::find_by_name('USER_ROLES');
	$all_roles = option_line::find_by_option_id($option_header->option_header_id);
	return $all_roles;
 }
 

}

$role_path = new role_path();
global $path_access;

if (!empty($_SESSION['user_id'])) {
 $path_access = -99;

 $role_path->assign_role_paths();
 
//check if admin role is assigned
 if (in_array('admin', $_SESSION['user_roles'])) {
	$path_access = 99;
 }
 
//check the role path access
 if ($path_access < 0) {
	$path_allowed = $role_path->check_path_access();
	if ($path_allowed) {
	 $path_access = 1;
	}
 }
   
}
?>
