<?php
require_once ('response.php');

global $USER_FILE;
class Login_Response extends Response {
    public string $User;

    function __construct(string $par1, bool $par2 = true) {
        parent::__construct('Login', $par2);
        $this->User = $par1;
    }
}

if ($_SERVER['REQUEST_METHOD'] != 'GET' || !isset($_GET['usr']) || !isset($_GET['pwd']))
    reject();

$usr = $_GET['usr'];
$pwd = $_GET['pwd'];
$data = $USER_FILE->read();
$response = new Login_Response($usr);

if (!isset($data[$usr]) || $pwd != $data[$usr]) {
    $response->Success = false;
    $response->ErrMessage = '用户名或密码错误！';
}

$response->sendWithOauth($usr);