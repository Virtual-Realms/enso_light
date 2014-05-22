<?php

$css = <<<CSS
/* this is a comment */
#selector .something > tag.something-else, 
.selector-second-line { 
display: block; 
width:100px; 
color: #ff0000; }

/* another comment this time longer */
#selector a { float:left; text-decoration:none }
CSS;


/**
 *  Simple function to parse CSS including comments into an array.
 */
function css2array($css)
{
  $results = array();

  // Find CSS comments and rules using regex voodoo
  $regex_comment = '/\*(.*?)\*/';
  $regex_selector = '(.*?)';
  $regex_declarations = '\{(.*?)\}';
  $regex_pattern = '#' . $regex_comment . $regex_selector . $regex_declarations . '#sm';
  preg_match_all($regex_pattern, $css, $matches);

  // Process each match 
  foreach($matches[0] AS $i=>$match)
  {
    $comment = trim($matches[1][$i]);
    $selector = trim($matches[2][$i]);
    $declarations = explode(';', $matches[3][$i]);
    foreach($declarations AS $declaration)
    {
      if (strlen(trim($declaration)) > 0) // for missing semicolon on last element, which is legal
      {
        list($property, $value) = explode(':', $declaration);
        $results[$comment][$selector][trim($property)] = trim($value);
      }
    }
  }
  return $results;
}


echo '<pre>';
print_r(css2array($css));
echo '</pre>';