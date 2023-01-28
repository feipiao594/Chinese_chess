<?php

class File {
    private $file = false;
    public string $filename;

    function __construct($par1) {
        $this->filename = $par1;
    }

    function read(): array
    {
        $this->file = fopen($this->filename, 'r');
        if ($this->file === false)
            reject();
        while (!flock($this->file, LOCK_SH))
            sleep(1);
        $data = file_get_contents($this->filename);
        fclose($this->file);
        $json = json_decode($data, JSON_OBJECT_AS_ARRAY);
        return $json ?: array();
    }

    function open(): array
    {
        $this->file = fopen($this->filename, 'r+');
        if ($this->file === false)
            reject();
        while (!flock($this->file, LOCK_EX))
            sleep(1);
        $data = fread($this->file, filesize($this->filename));
        $json = json_decode($data, JSON_OBJECT_AS_ARRAY);
        return $json ?: array();
    }

    function save(array &$data): void
    {
        fseek($this->file, 0);
        $size = fwrite($this->file, json_encode($data, JSON_FORCE_OBJECT));
        ftruncate($this->file, $size);
        fclose($this->file);
    }

    function close(): void
    {
        fclose($this->file);
    }
}

$USER_FILE = new File('userdata.json');
$OAUTH_FILE = new File('oauthdata.json');
$WAITING_ROOM = new File('waitingroom.json');
$GAME_FILE = new File('gamedata.json');
$MESSAGE_FILE = new File('messages.json');