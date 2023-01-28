<?php
require_once ('response.php');
global $USER_FILE;
class Signup_Response extends Response {
    function __construct(bool $par1 = true) {
        parent::__construct('Signup', $par1);
    }
}

if ($_SERVER['REQUEST_METHOD'] != 'GET' || !isset($_GET['usr']) || !isset($_GET['pwd']))
    reject();

$usr = $_GET['usr'];
$pwd = $_GET['pwd'];
$data = $USER_FILE->open();
$response = new Signup_Response();

if (isset($data[$usr])) {
    $response->Success = false;
    $response->ErrMessage = '该用户名已被注册！';
} else {
    $data[$usr] = $pwd;
    $USER_FILE->save($data);
}

$response->send();