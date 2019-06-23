<?php
/**
 * Project:     Securimage: A PHP class for creating and managing form CAPTCHA images<br />
 * File:        securimage_show.php<br />
*/

include 'securimage.php';

$img = new securimage();

$img->arc_linethrough =  false;
$img->code_length =  4;
$img->font_size =  18;
$img->image_height =  40;
$img->image_width =  130;
$img->text_maximum_distance = 30;
$img->text_minimum_distance =  25;

$img->show(); 

?>
