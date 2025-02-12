<?php

class user extends dbObject {

 public static $table_name = "user";
 public static $dependent_classes = ['user_role', 'user_password_reset'];
 public static $primary_column = "user_id";
 public static $key_column = 'username';
 public static $module = "extension";
 public static $system_info = [
		 'name' => 'User',
		 'number' => '9113',
		 'description' => 'Create & Update Users',
		 'version' => '1.1.1.3',
		 'db_version' => '1001',
		 'mod_version' => '1.1.x-1.1',
		 'dependent_class' => array('user_role', 'user_password_reset'),
		 'primary_entity_cb' => '',
		 'module_name' => 'ap',
		 'weight' => 13
 ];
//  data base variables as stored database column name
 public $field_a = [
		 "user_id",
		 "username",
		 "password",
		 "first_name",
		 "last_name",
		 "email",
		 "phone",
		 "created_by",
		 "creation_date",
		 "last_update_by",
		 "last_update_date"
 ];
//variables used for showing data
 public $initial_search = [
		 "user_id",
		 "username",
		 "first_name",
		 "last_name",
		 "email"
 ];
 public $column = [
		 "user_id",
		 "username",
		 "first_name",
		 "last_name",
		 "email"
 ];
 public $requiredField = [
		 "password",
		 "username",
		 "first_name",
		 "last_name",
		 "email"
 ];
 public $fields_inForm_notInDataBase = [
		 "enteredPassword",
		 "enteredRePassword",
 ];
 public $search = [
		 '_show_update_path' => 1,
		 '_update_action_meassge' => 'Update',
		 '_show_view_path' => 1,
		 '_extra_path' => array('form.php?class_name=user_role&mode=9' => 'Role')
 ];
 public $pageTitle = " User  "; //page Title
// public $option_lists = [
////		 'receipt_types' => 'AR_RECEIPT_TYPE',
////		 'po_status' => 'PO_STATUS',
// ];
// public $search_functions = [
//		 'Cost Type' => 'search_bom_cost_type',
//		  ];
 public $user_id;
 public $username;
 public $enteredPassword;
 public $enteredRePassword;
 public $password;
 Public $first_name;
 Public $last_name;
 public $phone;
 Public $email;
 Public $status;
 Public $laguage;
 Public $date_format;
 Public $theme;
 public $time;
 public $msg;

 public function _before_showing() {
	
 }

 public function _before_save() {
	if ($this->verify_user()) {
	 return 1;
	} else {
	 return -99;
	}
 }

 Public function findBy_userName($username) {
	$sql = " SELECT * FROM ";
	$sql .= self::$table_name;
	$sql .= " WHERE username = :username LIMIT 1";
	$value_a = ['username' => $username];
	$result = $this->findBySql($sql, $value_a);
	return !empty($result) ? array_pop($result) : false;
 }

 Public function findBy_eMail($email) {
	$sql = " SELECT * FROM ";
	$sql .= self::$table_name;
	$sql .= " WHERE email = :email LIMIT 1";
	$value_a = ['email' => $email];
	$result = $this->findBySql($sql, $value_a);
	return !empty($result) ? array_pop($result) : false;
 }

 Public static function find_by_email($email) {
	$sql = " SELECT * FROM ";
	$sql .= self::$table_name;
	$sql .= " WHERE email = '{$email}' LIMIT 1";
	$result = self::find_by_sql($sql);
	return !empty($result) ? array_pop($result) : false;
 }

 private function _codeThePassword($password) {
	return hash('sha256', crypt($password, 'xjkhrwq$@323sqjheq51234$$'));
 }

 public function authenticate($username = "", $password = "") {
	global $db;
//	$username = $db->escape_value($username);
//	$password = $db->escape_value($password);
////	$password_final = hash("sha256", $password);
	$password_final = $this->_codeThePassword($password);

	$sql = "Select user_id, username from user 
            WHERE username='{$username}' and password= '{$password_final}' LIMIT 1";
	$result_array = self::find_by_sql($sql);
	return !empty($result_array) ? array_shift($result_array) : false;
 }

 public function full_name() {
	if (isset($this->first_name) && isset($this->last_name)) {
	 return $this->first_name . " " . $this->last_name;
	} else {
	 return "";
	}
 }

 public static function check_email_userName($email, $userName) {
	global $db;
	$email = $db->escape_value($email);
	$sql = "SELECT * FROM user WHERE email='{$email}' OR username ='{$userName}'";
	$result_array = self::find_by_sql($sql);
	return !empty($result_array) ? true : false;
 }

 private function _check_email() {
	$sql = " SELECT * FROM user WHERE email= :email ";
	$value_a = ['email' => $this->email];
	$result_array = $this->findBySql($sql, $value_a);
	return !empty($result_array) ? true : false;
 }

 private function _check_userName() {
	$sql = " SELECT * FROM user WHERE username= :username ";
	$value_a = ['username' => $this->username];
	$result_array = $this->findBysql($sql, $value_a);
	return !empty($result_array) ? true : false;
 }

 public function verify_user() {
	//first check existing or new user 
	if (empty($this->user_id)) {
	 If ($this->_check_email()) {
		echo '<div class="message error">E-mail id is already associated with an user id<br/>
     <a href="' . $_SERVER['PHP_SELF'] . '#tabsLine-3">Reset your password</a></div>';
		$returnedData = false;
	 } else If ($this->_check_userName()) {
		echo '<div class="message error">Sorry, username is not available.<br/>
     Please try a differnt user name</div>';
		$returnedData = false;
	 } elseif ($this->enteredPassword == $this->enteredRePassword) {
		$this->password = $this->_codeThePassword($this->enteredPassword);
		$returnedData = true;
	 }//nonexisting user check 
	}//end of password match
	elseif ((!empty($this->user_id)) && (!empty($this->enteredPassword))) {
	 if ($this->enteredPassword == $this->enteredRePassword) {
		$this->password = $this->_codeThePassword($this->enteredPassword);
		$returnedData = true;
	 }
	} elseif ((!empty($this->user_id)) && (empty($this->enteredPassword))) {
	 $existing_user = new user();
	 $existing_user->findBy_id($this->user_id);
	 $this->password = $existing_user->password;
	 $returnedData = true;
	}
	return $returnedData;
 }

 public function _after_save() {
	global $db;
	global $si ;
	if ($this->user_id) {
	 $msg = "New user registration is sucessful!";
	 $to = $this->email;
	 $subject = "User Registrtion @ " . $si->site_name;
	 $message = "Dear " . $this->username . '<br> your regitraton is sucessful';
	 $replyto = "From : admin@site.com";

	 if (mail($to, $subject, $message)) {
		$msg = "mail has been sent";
	 } else {
		$msg = "mail failed!";
	 }//email complete
	}//new user registration complete
	else {
	 $msg = "New user registration Failed!" . mysql_error();
	}// registraion failed
	return $this->msg;
 }

}

//end of resource class
?>



