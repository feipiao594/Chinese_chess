<?php
require_once ('response.php');

class Find_Response extends Response {
    public string $Opp;
    public bool $Side;

    public function __construct() {
        parent::__construct('Find');
    }

    public function fillWith(array $info): void {
        $this->Opp = $info['Opp'];
        $this->Side = $info['Side'];
    }

    public function send(): void {
        if ($this->Success)
            http_response_code(201);
        parent::send();
    }
}

function mustWait(array &$data, string $usr): bool {
    if (isset($data[$usr]) && $data[$usr]['found'])
        return false;
    foreach ($data as $name=>$datum)
        if ($name != $usr && !$datum['found'])
            return false;
    return true;
}

function add(array &$data, string $usr, int $wait): void {
    $info = array('found' => false, 'wait' => $wait);
    $data[$usr] = $info;
}

function getOpp(array &$data, string $usr): array {
    if (isset($data[$usr]) && $data[$usr]['found'])
        return $data[$usr];
    $info = array('wait' => -1);

    foreach ($data as $name=>$datum)
        if ($name != $usr && !$datum['found'] && $datum['wait'] > $info['wait']) {
            $info = $datum;
            $info['Opp'] = $name;
        }
    return $info;
}

function makeBoard(string $usr, array $info, Find_Response &$response): void {
    $info['Side'] = (rand(0, 1) == 1);
    $response->fillWith($info);

    global $GAME_FILE;
    $id = uniqid();
    $data = $GAME_FILE->open();
    $data['id'][$usr] = array('id' => $id, 'side' => $info['Side']);
    $data['id'][$response->Opp] = array('id' => $id, 'side' => !$info['Side']);
    $GAME_FILE->save($data);

    global $MESSAGE_FILE;
    $data = $MESSAGE_FILE->open();
    $data['id'][$usr] = $id;
    $data['id'][$response->Opp] = $id;
    $MESSAGE_FILE->save($data);
}

function notifyOpp(array &$data, string $usr, string $opp, bool $side): void {
    $info = array('found' => true, 'Opp' => $usr, 'Side' => $side);
    $data[$opp] = $info;
}

verifyOauth();
$usr = $_GET['usr'];
if (!isset($_GET['wait']))
    reject();
$wait = $_GET['wait'];
$response = new Find_Response();
global $WAITING_ROOM;
$data = $WAITING_ROOM->open();
if (mustWait($data, $usr)) {
    add($data, $usr, $wait);
    $response->Success = false;
    $response->ErrMessage = "请耐心等待，正在全力匹配玩家……";
}
else {
    $info = getOpp($data, $usr);
    if (isset($info['Side'])) {
        $response->fillWith($info);
        unset($data[$usr]);
    } else {
        makeBoard($usr, $info, $response);
        notifyOpp($data, $usr, $response->Opp, !$response->Side);
    }
}
$WAITING_ROOM->save($data);
$response->sendWithOauth($usr);