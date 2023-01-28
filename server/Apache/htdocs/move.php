<?php
require_once ('response.php');

verifyOauth();
$usr = $_GET['usr'];
if (!isset($_GET['X1']) || !isset($_GET['Y1']) || !isset($_GET['X2']) || !isset($_GET['Y2']))
    reject();
$response = new Response();
global $GAME_FILE;
$data = $GAME_FILE->open();
$info = $data['id'][$usr];
$id = $info['id'];
$side = $info['side'];
$move = array('Side' => $side, 'X1' => $_GET['X1'], 'Y1' => $_GET['Y1'], 'X2' => $_GET['X2'], 'Y2' => $_GET['Y2']);
$data[$id] = $move;
$GAME_FILE->save($data);
$response->sendWithOauth($usr);