<?php

use JetBrains\PhpStorm\NoReturn;

require_once ('file.php');

#[NoReturn] function reject(): void {
    http_Response_code(404);
    die('404 NOT FOUND');
}

class OAuthInfo {
    const DEFAULT_EXPIRE_TIME = 3600;
    const DEFAULT_RENEW_TIME = 1800;
    private string $usr;
    private int $create;
    private int $expire = 0;
    public string $token;

    function __construct(string $par1) {
        $this->usr = $par1;

        global $OAUTH_FILE;
        $data = $OAUTH_FILE->read();
        if (isset($data[$this->usr])) {
            $info = $data[$this->usr];
            $this->token = $info['token'];
            $this->expire = $info['expire'];
            $this->create = $info['create'];
        }
    }

    function tokenValid(): bool {
        return time() < $this->expire;
    }
    function setHeader(): void {
        if (!$this->tokenValid() || time() - $this->create > self::DEFAULT_RENEW_TIME) {
            $this->create = time();
            $this->expire = $this->create + self::DEFAULT_EXPIRE_TIME;
            $this->token = uniqid();
            global $OAUTH_FILE;

            $data = $OAUTH_FILE->open();
            $data[$this->usr] = array('create' => $this->create, 'expire' => $this->expire, 'token' => $this->token);
            $OAUTH_FILE->save($data);
        }
        setcookie('token', $this->token, $this->expire);
    }

    function compare(string $token): bool {
        if (!$this->tokenValid())
            return false;
        return $this->token == $token;
    }
}

function addOauth(string $usr): void
{
    $info = new OAuthInfo($usr);
    $info->setHeader();
}

function verifyOauth(): void
{
    $failed = false;
    if ($_SERVER['REQUEST_METHOD'] != 'GET' || !isset($_GET['usr']))
        $failed = true;
    $usr = $_GET['usr'];
    $info = new OAuthInfo($usr);
    $token = null;
    if (isset($_COOKIE['token']))
        $token = $_COOKIE['token'];

    if (!$token || !$info->compare($token))
        $failed = true;

    if ($failed)
        reject();

    $info->setHeader();
}