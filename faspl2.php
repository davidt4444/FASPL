<style type="text/css">
h3, h4
{
	padding:0px;
	margin:0px;
}

</style>
<?


//phpinfo();

$myFile = "temp.faspl";
$fh = fopen($myFile, 'w') or die("can't open file");
fwrite($fh, stripslashes ($_POST['code']));
fclose($fh);

$myFile = "temp.input";
$fh = fopen($myFile, 'w') or die("can't open file");
fwrite($fh, stripslashes ($_POST['input']));
fclose($fh);


?>

<h3>Web based FASPL</h3>

<form name="input" action="faspl.php" method="post">
<h4>Code</h4>
<textarea name="code" rows="9" cols="100">
<?
echo stripslashes ($_POST['code']);
?>
</textarea> 
<br />
<h4>STD Input (experimental)</h4>
<textarea name="input" rows="3" cols="100">
<?
echo stripslashes ($_POST['input']);
?>
</textarea> 
<br />
<input type="submit" value="Submit">

</form> 

<h4>STD Output</h4>
<textarea rows="3" cols="100">
<?
//echo $_POST['code'];

    function runExternal($cmd,&$code) {
        $descriptorspec = array(
            0 => array("pipe", "r"),  // stdin is a pipe that the child will read from
            1 => array("pipe", "w"),  // stdout is a pipe that the child will write to
            2 => array("pipe", "w") // stderr is a file to write to
        );
       
        $pipes= array();
        $process = proc_open($cmd, $descriptorspec, $pipes);
       
        $output= "";
       
        if (!is_resource($process)) return false;
       
        #close child's input imidiately
        fclose($pipes[0]);
       
        stream_set_blocking($pipes[1],false);
        stream_set_blocking($pipes[2],false);
       
        $todo= array($pipes[1],$pipes[2]);
       
        while( true ) {
            $read= array();
            if( !feof($pipes[1]) ) $read[]= $pipes[1];
            if( !feof($pipes[2]) ) $read[]= $pipes[2];
           
            if (!$read) break;
           
            $ready= stream_select($read, $write=NULL, $ex= NULL, 2);
           
            if ($ready === false) {
                break; #should never happen - something died
            }
           
            foreach ($read as $r) {
                $s= fread($r,1024);
                $output.= $s;
            }
        }
       
        fclose($pipes[1]);
        fclose($pipes[2]);
       
        $code= proc_close($process);
       
        return $output;
    }



if($_POST['code']!=""){
echo runExternal('./faspl temp.faspl < temp.input', &$error);
}

//echo $error;
//echo shell_exec('cat temp.faspl');
//echo shell_exec('cat a.xddl');
//echo shell_exec('cat a.output');
//echo shell_exec('cat temp.faspl');

?>
</textarea> 


<h4>XML Output</h4>
<textarea rows="9" cols="100">
<?
if($_POST['code']!=""){
echo shell_exec('cat a.xddl');
}
//echo shell_exec('cat a.output');
//echo shell_exec('cat temp.faspl');

?>
</textarea> 