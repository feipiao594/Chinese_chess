<?php
require_once ('oauth.php');
class Response
{
    public string $Type;
    public bool $Success;
    public string|null $ErrMessage = null;

    function __construct(string $par1 = 'Continue', bool $par2 = true) {
        $this->Type = $par1;
        $this->Success = $par2;
    }

    function send(): void
    {
        $content = json_encode($this);
        header('Content-type:application/json;charset=utf-8');
        echo $content;
    }

    function sendWithOauth(string $usr): void
    {
        addOauth($usr);
        $this->send();
    }
}

class Continue_Response extends Response {
    public function __construct(string $par1 = 'Continue') {
        parent::__construct($par1);
    }

    public function send(): void {
        http_Response_code(201);
        parent::send();
    }
}

class Message_Response extends Continue_Response {
    public string $Message;

    public function __construct(string $par1) {
        parent::__construct('Message');
        $this->Message = $par1;
    }
}

class Move_Response extends Continue_Response {
    public int $X1;
    public int $Y1;
    public int $X2;
    public int $Y2;

    public function __construct() {
        parent::__construct('Move');
    }

    public function fillWith(array $info): void {
        $this->X1 = 10 - $info['X1'];
        $this->Y1 = 11 - $info['Y1'];
        $this->X2 = 10 - $info['X2'];
        $this->Y2 = 11 - $info['Y2'];
    }
}