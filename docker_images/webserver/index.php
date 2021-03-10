<html>
  <head>
    <title>The Boeing Blog</title>
    <meta charset="utf-8"/>
    <link type='text/css' rel='stylesheet' href='style.css'/>
  </head>
  <body>
    <ul>
      <li><a href='index.php'>Home</a></li>
      <li><a href='about.html'>About Us</a></li>
      <li><a href='upload.php'>Upload</a></li>
      <li><a href='#'>Customer Service</a></li>
    </ul>

    <h1>Welcome to the Boeing Blog!</h1>
    <img src='https://www.gannett-cdn.com/-mm-/eda357dd8751dcdcc72d351adb3b8d1bdcafcb38/c=0-129-2500-1535/local/-/media/2020/07/09/USATODAY/usatsports/boeing-737-max-on-tug-source-ba.jpg?width=660&height=372&fit=crop&format=pjpg&auto=webp'/>
    <hr>
    <div id='content'>
      <?php

        // ini_set('display_errors', 1);
        // ini_set('display_startup_errors', 1);
        // error_reporting(E_ALL);

        if(!$link = mysql_connect('localhost', 'root', 'Tot@llyS3cUr3P@ssword!')) {
          echo "Cannot connect to database!";
        }
        if(!mysql_select_db('site', $link)) {
          echo "Couldn't select table";
        }

        if(!isset($_GET["post"]) || $_GET["post"] == "") {
          $sql = "SELECT id FROM site order by id";

          $result = mysql_query($sql, $link);

          echo "<h4>List of Posts</h4>";
          echo "<ul>";

          while ($row = mysql_fetch_assoc($result)) {
            echo "<li><a href='index.php?post={$row['id']}'>Post #" . $row['id'] . "</a></li>";
          }
          echo "</ul>";
        }
        else {
          $post = $_GET["post"];

          $sql = "SELECT * FROM site where id='$post'";

          $result = mysql_query($sql, $link);

          if (!$result) {
              echo "DB Error, could not query the database\n";
              echo 'MySQL Error: ' . mysql_error();
              exit;
          }

          while ($row = mysql_fetch_assoc($result)) {
              echo $row['content'];
          }
        }

        mysql_free_result($result);
      ?>
    </div>
  </body>
</html>
