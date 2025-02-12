<?php

class dbObject {

// protected static $table_name = "";
//  data base variables as stored database column name
 public static $field_array = [];
//variables used for showing data

 public static $initial_search_array = [];
 public static $checkbox_array = [];
 public static $column_array = [];
 public static $requiredField_array = [];
 public static $position_array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25];
 public static $key_column = '';
 public static $parent_primary_column = null;
 public $time;
 public $msg;
 public $conn;
 public $field_a = [];

 function __construct() {
//	if (!empty(static::$table_name)) {
////	 echo '<br> table name '. static::$table_name;
//	 global $dbc;
//	 $sql_fields = " SHOW COLUMNS FROM  " . static::$table_name;
//	 $prepare = $dbc->connection->prepare($sql_fields);
//	 $prepare->execute();
//	 $fields = $prepare->fetchAll(PDO::FETCH_COLUMN, 0);
//	 static::$field_array = $fields;
//	 foreach ($fields as $key => $value) {
//		$this->$value = '';
//	 }
//	}
 }

 public function __set($name, $value) {
	$this->$name = $value;
 }

 public function get($var) {
	if (property_exists(get_called_class(), $var)) {
	 return $this->$var;
	} else {
	 return false;
	}
 }

 function query($sql) {
	echo "sql is $sql";
	global $dbc;
	if (!empty($sql)) {
	 $prepare = $dbc->connection->prepare($sql);
	 try {
		$prepare->execute();
		$result = $prepare->fetchAll(PDO::FETCH_CLASS);
		return $result;
	 } catch (PDOException $e) {
		print " Execution failed! in dbObject Query: " . $e->getMessage() . "<br/>";
	 }
	}
 }

// public function findBy_parentHeaderId($header_id) {
//	if (!empty(parent::$primary_column)) {
//	 $sql = "SELECT * FROM " . parent::$table_name . " where " . parent::$primary_column . " = '{$header_id}'";
//	 $result_array = $this->findBy_sql($sql);
//	} else {
//	 $result_array = false;
//	}
//	return $result_array;
// }

 public function findBy_sql($sql, $param_a = '', $value_a = '') {
	global $dbc;
	$stmt = $dbc->connection->prepare(" $sql ");
	if (!empty($param_a)) {
	 foreach ($param_a as $key => $param) {
		if (!empty($value_a[$param])) {
		 $stmt->bindValue(":$param", $value_a[$param]);
		} else {
		 $stmt->bindValue(":$param", NULL);
		}
	 }
	}
	try {
	 $stmt->execute();
	 $result = $stmt->fetchAll(PDO::FETCH_CLASS);
	 return $result;
	} catch (PDOException $e) {
	 echo "Record couldnt be fetched !!: " . $e->getMessage();
	 return 0;
	}
 }

// public function findBySql($sql, $value_a = '') {
//	global $dbc;
//	$stmt = $dbc->connection->prepare(" $sql ");
//	if (!empty($value_a)) {
//	 foreach ($value_a as $key => $value) {
//		if (!empty($value)) {
//		 $stmt->bindValue(":$key", $value);
//		} else {
//		 $stmt->bindValue(":$key", NULL);
//		}
//	 }
//	}
//	try {
//	 $stmt->execute();
//	 $result = $stmt->fetchAll(PDO::FETCH_CLASS);
//	 return $result;
//	} catch (PDOException $e) {
//	 echo "Record couldnt be fetched !!: " . $e->getMessage();
//	 return 0;
//	}
// }

 public function findBySql($sql, $value_a = '') {
	global $dbc;
	$stmt = $dbc->connection->prepare(" $sql ");
	if (!empty($value_a)) {
	 foreach ($value_a as $key => $value) {
		if (!empty($value)) {
		 if ($key == 'lmt_no_of_records' || $key == 'lmt_start_from') {
			$stmt->bindValue(":$key", $value, PDO::PARAM_INT);
		 } else {
			$stmt->bindValue(":$key", $value);
		 }
		} else {
		 $stmt->bindValue(":$key", NULL);
		}
	 }
	}
	try {
	 $stmt->execute();
	 $result = $stmt->fetchAll(PDO::FETCH_CLASS);
	 return $result;
	} catch (PDOException $e) {
	 echo "Record couldnt be fetched !!: " . $e->getMessage();
	 return 0;
	}
 }

 public function findBySql_array($sql = "") {
	global $dbc;
	$prepare = $dbc->connection->prepare($sql);
	$prepare->execute();
	$result = $prepare->fetchAll(PDO::FETCH_NUM);
	return $result;
 }

 public function findFirstColumn_BySql_array($sql = "") {
	global $dbc;
	$prepare = $dbc->connection->prepare($sql);
	$prepare->execute();
	$result = $prepare->fetchAll(PDO::FETCH_COLUMN);
	return $result;
 }

 /* End of public functions and start of public static functions  */

 public static function show_column_from_table($tableName = "") {
	global $dbc;
	$sql = " SHOW COLUMNS FROM $tableName ";
	$prepare = $dbc->connection->prepare($sql);
	$prepare->execute();
	$result_fetchAll = $prepare->fetchAll(PDO::FETCH_COLUMN, 0);
	return $result_fetchAll;
 }

 public static function show_allColumn_from_table($tableName = "") {
	global $dbc;
	$sql = " SHOW COLUMNS FROM $tableName ";
	$prepare = $dbc->connection->prepare($sql);
	$prepare->execute();
	$result_fetchAll = $prepare->fetchAll(PDO::FETCH_CLASS);
	return $result_fetchAll;
 }

 public static function show_table_details($tableName = "") {
	global $dbc;
	$sql = " SHOW COLUMNS FROM $tableName ";
	$prepare = $dbc->connection->prepare($sql);
	$prepare->execute();
	$result_fetchAll = $prepare->fetchAll(PDO::FETCH_CLASS);
	return $result_fetchAll;
 }

 public static function find_by_sql($sql = "") {
	global $dbc;
	$prepare = $dbc->connection->prepare($sql);
	$prepare->execute();
	$result_fetchAll = $prepare->fetchAll(PDO::FETCH_CLASS);
	return $result_fetchAll;
 }

 public static function find_by_sql_array($sql = "") {
	global $dbc;
	$prepare = $dbc->connection->prepare($sql);
	$prepare->execute();
	$result = $prepare->fetchAll(PDO::FETCH_NUM);
	return $result;
 }

 public static function find_by_sql_all($sql = "") {
	global $dbc;
	$prepare = $dbc->connection->prepare($sql);
	$prepare->execute();
	$result_fetchAll = $prepare->fetchAll();
	return $result_fetchAll;
 }

 public static function find_all() {
	$sql = " SELECT * FROM " . static::$table_name;
	$result = static::find_by_sql($sql);
	return $result;
 }

 public static function find_few($no_of_records = 2) {
	$sql = " SELECT * FROM " . static::$table_name . " LIMIT $no_of_records ";
	$result = static::find_by_sql($sql);
	return $result;
 }

 public static function find_some_byIdArray($id_array) {
	$result_array = [];
	foreach ($id_array as $key => $value) {
	 $result = static::find_by_id($value);
	 array_push($result_array, $result);
	}
	return $result_array;
 }

 public static function count_all() {
	$sql = "SELECT COUNT(*) FROM " . static::$table_name;
	$result = static::find_by_sql_array($sql);
	return !empty($result) ? array_shift2($result) : false;
 }

 public static function count_all_by_sql($sql) {
	$result = static::find_by_sql_array($sql);
	return !empty($result) ? array_shift2($result) : false;
 }

 public static function find_by_id($id) {
	global $ie;
	global $dbc;
	$sql = " SELECT * FROM ";
	$sql.= static::$table_name;
	$sql.= " WHERE " . static::$primary_column . "= :primary_id ";
	$sql.= " LIMIT 1 ";
	$stmt = $dbc->connection->prepare(" $sql ");
	$stmt->bindParam(':primary_id', $id);
	try {
	 $stmt->execute();
	 $result = $stmt->fetchObject();
	} catch (PDOException $e) {
	 $ie->page_exception = ['dbObject findBy id Error : ' => $e->getMessage()];
	 echo "Record couldnt be saved!!: " . $e->getMessage();
	}
	return $result;
 }

 public function findAll() {
	global $ie;
	global $dbc;
	$sql = " SELECT * FROM ";
	$sql.= static::$table_name;
	$stmt = $dbc->connection->prepare(" $sql ");
	try {
	 $stmt->execute();
	 $result = $stmt->fetchAll(PDO::FETCH_CLASS);
	} catch (PDOException $e) {
	 $this->msg = "No Records Found" . $e->getMessage();
	}
	return !empty($result) ? $result : false;
 }

 public function findBy_id($id) {
	global $ie;
	global $dbc;
	$sql = " SELECT * FROM ";
	$sql.= static::$table_name;
	$sql.= " WHERE " . static::$primary_column . "= :primary_id ";
	$sql.= " LIMIT 1 ";
	$stmt = $dbc->connection->prepare(" $sql ");
	$stmt->bindParam(':primary_id', $id);
	$stmt->setFetchMode(PDO::FETCH_INTO, $this);
	try {
	 $stmt->execute();
//	 $result = $stmt->fetchObject();
	 $result = $stmt->fetch();
	} catch (PDOException $e) {
	 $this->msg = "No Records Found" . $e->getMessage();
	}
	if (!empty($result)) { //should not be used. Use only when a copy of the class is required
	 return $result;
	} else {
	 return "No Records Found!";
	}
 }

 public function findBy_parentId($id, $order_by_field = '', $order_by_seq = 'ASC') {
	if (empty($id)) {
	 return false;
	}
	global $ie;
	global $dbc;
	$sql = " SELECT * FROM ";
	$sql.= static::$table_name;
	$sql.= " WHERE " . static::$parent_primary_column . "= :primary_id ";
	if (!empty($order_by_field)) {
	 $sql.= " ORDER BY {$order_by_field} $order_by_seq ";
	}
	$stmt = $dbc->connection->prepare(" $sql ");
	$stmt->bindParam(':primary_id', $id);
	try {
	 $stmt->execute();
	 $result = $stmt->fetchAll(PDO::FETCH_CLASS);
	} catch (PDOException $e) {
	 $ie->page_exception = ['dbObject findBy parent id Error : ' => $e->getMessage()];
	}
	if (!empty($result)) {
	 return $result;
	} else {
	 $ie->page_exception = ['dbObject findBy parent id Error : ' => 'No records found'];
	 return false;
	}
 }

 public static function find_by_id_array($id) {
	global $dbc;
	$sql = "SELECT * FROM " . static::$table_name . " where `" . static::$primary_column . "` ='{$id}'  LIMIT 1";
	$result_array = static::find_by_sql_array($sql);
	return !empty($result_array) ? array_shift($result_array) : false;
 }

 public static function find_by_keyColumn($columnName) {
	$sql = "SELECT * FROM " . static::$table_name . " where `" . static::$key_column . "` ='{$columnName}'  LIMIT 1";
	$result_array = static::find_by_sql($sql);
	return !empty($result_array) ? array_shift($result_array) : false;
 }

 public static function find_by_keyColumn_array($columnName) {
	global $dbc;
	$sql = "SELECT * FROM " . static::$table_name . " where `" . static::$columnName . "` ='{$columnName}'  LIMIT 1";
	$result_array = static::find_by_sql_array($sql);
	return !empty($result_array) ? array_shift($result_array) : false;
 }

 private static function instantiate($record) {
	$object = new static;
	foreach ($record as $attribute => $value) {
	 if ($object->has_attribute($attribute)) {
		$object->$attribute = $value;
	 }
	}
	return $object;
 }

 Private function has_attribute($attribute) {
	$object_vars = get_object_vars($this);
	return array_key_exists($attribute, $object_vars);
 }

 public function audit_trial() {
	if (empty($this->creation_date)) {
	 $this->creation_date = current_time();
	}
	if (empty($this->created_by)) {
	 if ((isset($_SESSION)) && (!empty($_SESSION['username']))) {
		$this->created_by = $_SESSION['username'];
	 } else {
		$this->created_by = 'selfWeb';
	 }
	}
	$this->last_update_date = current_time();
	if ((isset($_SESSION)) && (!empty($_SESSION['username']))) {
	 $this->last_update_by = $_SESSION['username'];
	} else {
	 $this->last_update_by = 'selfWeb';
	}
 }

 public function save() {
	$primary_column = static::$primary_column;
	if (empty($this->$primary_column)) {
	 $this->create();
	} else {
	 $this->update_changesOnly($this->$primary_column);
	}
	return $this->msg;
 }

 public function save_onWebForm() {
	$primary_column = static::$primary_column;
	if (empty($this->$primary_column)) {
	 $this->create();
	} else {
	 $this->update($this->$primary_column);
	}
	return $this->msg;
 }

 public function create() {
	global $dbc;
	$parent_class_name = get_called_class();
	if (property_exists($parent_class_name, 'primary_column')) {
	 $primary_column = static::$primary_column;
	}
	if (property_exists($this, 'field_a')) {
	 $field_array = $this->field_a;
	} else {
	 $field_array = static::$field_array;
	}

	$field_colums = '';
	foreach ($field_array as $key => $value) {
	 $field_colums .= $value . ', ';
	}
	$field_colums = rtrim($field_colums, ', ');

	$field_values = '';
	foreach ($field_array as $key => $value) {
	 $field_values .= ':' . $value . ', ';
	}
	$field_values = rtrim($field_values, ', ');
//write SQL
	$sql = " INSERT INTO ";
	$sql.= static::$table_name;
	$sql.= ' ( ';
	$sql.= $field_colums;
	$sql.= ' ) ';
	$sql.= 'VALUES';
	$sql.= ' ( ';
	$sql.= $field_values;
	$sql.= ' ) ';
	$stmt = $dbc->connection->prepare(" $sql ");

	//Bind parameters
	foreach ($field_array as $key => $value) {
	 if (!empty($this->$value)) {
		$stmt->bindParam(":$value", $this->$value);
	 } else {
		$stmt->bindvalue(":$value", null, PDO::PARAM_INT);
	 }
	}
	try {
	 $stmt->execute();
	 if (isset($primary_column)) {
		$this->$primary_column = $dbc->connection->lastInsertId();
	 }
	 $this->msg = 1;
	} catch (PDOException $e) {
	 $this->msg = 0;
	 echo "Record couldnt be saved!!: Error Code : DBO01 " . $e->getMessage() . "<br/>";
	}
	return $this->msg;
 }

//update function
 public function update($id) {
	global $dbc;
	if (property_exists($this, 'field_a')) {
	 $field_array = $this->field_a;
	} else {
	 $field_array = static::$field_array;
	}
	$field_stmt = '';
	foreach ($field_array as $key => $value) {
	 $field_stmt .= $value . ' = :' . $value . ', ';
	}
	$field_stmt_f = rtrim($field_stmt, ', ');
//write SQL
	$sql = " UPDATE ";
	$sql.= static::$table_name;
	$sql .= " SET ";
	$sql.= $field_stmt_f;
	$sql.= " WHERE " . static::$primary_column . "= :primary_id ";

	$stmt = $dbc->connection->prepare(" $sql ");
	//Bind parameters
	foreach ($field_array as $key => $value) {
	 $stmt->bindParam(":$value", $this->$value);
	}
	$time = time();
	$last_update_date = strftime("%d-%m-%y %H:%M:%S", $time);
	if (!empty($_SESSION['user_name'])) {
	 $last_update_by = $_SESSION['user_name'];
	} else {
	 $last_update_by = 'admin';
	}
	$stmt->bindParam(':last_update_by', $last_update_by);
	$stmt->bindParam(':last_update_date', $last_update_date);
	$stmt->bindParam(':primary_id', $id);
	try {
	 $stmt->execute();
	 $this->msg = 1;
	} catch (PDOException $e) {
	 $this->msg = 0;
	 echo "<div class='message'>failing for sql is $sql</div>";
	 echo "Record could not be updated !!: " . $e->getMessage();
	}
	return $this->msg;
 }

 public function update_changesOnly($id) {
	global $dbc;

	if (property_exists($this, 'field_a')) {
	 $field_array = $this->field_a;
	} else {
	 $field_array = static::$field_array;
	}
	$field_stmt = '';
	foreach ($field_array as $key => $value) {
	 if (isset($this->$value)) {
		$field_stmt .= $value . ' = :' . $value . ', ';
	 }
	}
	$field_stmt_f = rtrim($field_stmt, ', ');
//write SQL
	$sql = " UPDATE ";
	$sql.= static::$table_name;
	$sql .= " SET ";
	$sql.= $field_stmt_f;
	$sql.= " WHERE " . static::$primary_column . "= :primary_id ";
	$stmt = $dbc->connection->prepare(" $sql ");
//Bind parameters
	foreach ($field_array as $key => $value) {
	 if (isset($this->$value)) {
		$stmt->bindParam(":$value", $this->$value);
	 }
	}
	$time = time();
	$last_update_date = strftime("%d-%m-%y %H:%M:%S", $time);
	if (!empty($_SESSION['user_name'])) {
	 $last_update_by = $_SESSION['user_name'];
	} else {
	 $last_update_by = 'admin';
	}
	$stmt->bindParam(':last_update_by', $last_update_by);
	$stmt->bindParam(':last_update_date', $last_update_date);
	$stmt->bindParam(':primary_id', $id);
	try {
	 $stmt->execute();
	 $this->msg = 1;
	} catch (PDOException $e) {
	 $this->msg = 0;
	 echo "<div class='message'>failing for sql is $sql</div>";
	 echo "Record could not be updated !!: " . $e->getMessage();
	}
	return $this->msg;
 }

 public function delete() {
	global $dbc;
	$primary_column = static::$primary_column;
	$sql = " DELETE FROM ";
	$sql .= static::$table_name;
	$sql .= " WHERE  ";
	$sql .= $primary_column . "= :primary_column ";

	$stmt = $dbc->connection->prepare($sql);
	$stmt->bindParam(':primary_column', $this->$primary_column);
//	echo '<div class="message"><br/>$sql is : ' . $sql . ' and primary column is' . $this->$primary_column . '</div>';
	try {
	 $stmt->execute();
	 $this->msg = 1;
	 echo "<div class='message'>Record is sucessfully deleted.</div>";
	} catch (PDOException $e) {
	 $this->msg = 0;
	 echo "<div class='message'>failing for sql is $sql</div>";
	 echo "Record could not be updated !!: " . $e->getMessage();
	}
	return $this->msg;
 }

 public function deleteBy_parentId($id) {
	if (empty($id)) {
	 return false;
	}
	$dbc = new dbc();
	$sql = " DELETE FROM  ";
	$sql.= static::$table_name;
	$sql.= " WHERE " . static::$parent_primary_column . "= :primary_id ";
	$stmt = $dbc->connection->prepare($sql);
	$stmt->bindParam(':primary_id', $id);
	try {
	 $stmt->execute();
//	 $dbc->connection->commit();
	 $this->msg = 1;
	 echo "<div class='message'>Records are sucessfully deleted.</div>";
	} catch (PDOException $e) {
	 $this->msg = 0;
	 echo "<div class='message'>failing for sql is $sql</div>";
	 echo "Record could not be updated !!: " . $e->getMessage();
	}
	return $this->msg;
 }

 protected function deleteBy_orgId($org_id) {
	if (empty($id)) {
	 return false;
	}
	$dbc = new dbc();
	$sql = " DELETE FROM  ";
	$sql.= static::$table_name;
	$sql.= " WHERE org_id = :org_id ";
	$stmt = $dbc->connection->prepare($sql);
	$stmt->bindParam(':org_id', $org_id);
	try {
	 $stmt->execute();
//	 $dbc->connection->commit();
	 $this->msg = 1;
	 echo "<div class='message'>Records are sucessfully deleted.</div>";
	} catch (PDOException $e) {
	 $this->msg = 0;
	 echo "<div class='message'>failing for sql is $sql</div>";
	 echo "Record could not be updated !!: " . $e->getMessage();
	}
	return $this->msg;
 }

// public static function delete($id) {
//	global $dbc;
//
//	$sql = " DELETE FROM ";
//	$sql .= static::$table_name;
//	$sql .= " WHERE  ";
//	$sql .= static::$primary_column . "= '{$id}' ";
//
////	echo '<div class="message"><br/>$sql is : '. $sql. '</div>';
//	$prepare = $dbc->connection->prepare($sql);
//
//	if ($prepare->execute()) {
//	 return true;
//	} else {
//	 return false;
//	}
// }
}

//end of content_type class

$dbObject = new dbObject();
$db = & $dbObject;
?>