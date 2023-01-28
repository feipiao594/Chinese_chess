<?php
require_once ('response.php');

verifyOauth();
$usr = $_GET['usr'];
if (!isset($_GET['message']))
    reject();
$message = $_GET['message'];
$response = new Response();
global $MESSAGE_FILE;
$data = $MESSAGE_FILE->open();
$id = $data['id'][$usr];
$data[$id][] = array('uid' => $usr, 'message' => $message);
$MESSAGE_FILE->save($data);
$response->sendWithOauth($usr);