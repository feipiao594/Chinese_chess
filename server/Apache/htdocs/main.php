<?php
require_once ('response.php');

const DEFAULT_WAIT_TIME = 2;
$timer = time();
verifyOauth();
$usr = $_GET['usr'];
$response = false;
while (time() < $timer + DEFAULT_WAIT_TIME) {
    global $GAME_FILE;
    $data = $GAME_FILE->open();
    $info = $data['id'][$usr];
    $id = $info['id'];
    $side = $info['side'];
    if (isset($data[$id]) && $data[$id]['Side'] == !$side) {
        $move = $data[$id];
        $response = new Move_Response();
        $response->fillWith($move);
        unset($data[$id]);
        $GAME_FILE->save($data);
        break;
    }
    $GAME_FILE->close();

    global $MESSAGE_FILE;
    $data = $MESSAGE_FILE->open();
    if (!isset($data[$id]) || count($data[$id]) == 0) {
        $MESSAGE_FILE->close();
        continue;
    }
    foreach($data[$id] as $index=>$datum)
        if ($datum['uid'] != $usr) {
            $response = new Message_Response($datum['message']);
            unset($data[$id][$index]);
            $MESSAGE_FILE->save($data);
            break;
        }
}
if (!$response)
    $response = new Continue_Response();
$response->sendWithOauth($usr);