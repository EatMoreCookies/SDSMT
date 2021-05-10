<html>
<header>
    <link rel="stylesheet" href="css/index.css" />
    <script type="text/javascript" src="js/FileManage.js"></script>
    <div class="header">
        <h1>Manage Files</h1>
    </div>
    <div>
        <nav class="nav">
            <a href="index.php">Home</a>
            <a href="FileManagement.php">Manage Files</a>
            <a href="HelpPage.html">Help</a>
        </nav>
    </div>
</header>
<body>
<br/>


<div class="loadImage">

    <form action="FileManagement.php?up=1" method="post" enctype="multipart/form-data">
        Select file to upload:

        <!--name and id are used as identifiers of the file on the php side-->
        <input type="file" name="fileToUpload" id="fileToUpload">
        <input type="submit" value="Upload" name="submit">
    </form>

    <!--basic structure for a file upload-->
    <?php
    ini_set('display_errors', true);
    error_reporting(E_ALL);
    require_once "Upload.php";
    //determine what to do based on GET variables
    if (isset($_GET['up'])) {
        upload();
    }

    if( isset($_GET['delete'])){
        if(!unlink("/home/student/7416949/www/uploads/".$_GET['delete']))
            echo"Unable to Delete ".$_GET['delete'];
    }

    if ($handle = opendir('uploads/')) {

        while (false !== ($entry = readdir($handle))) {

            if ($entry != "." && $entry != "..") {
                echo '<p><li>' . $entry . '<a id="downloadLink" href="uploads/'.$entry.'">Download</a>
                        <button class="buttonStd" onclick="Load(\''.$entry .'\')">Load</button>
                         <button class="buttonStd" onclick="Delete(\''.$entry .'\')">Delete</button></p>';
            }
        }

        closedir($handle);
    }
    ?>

</div>
</body>
</html>
