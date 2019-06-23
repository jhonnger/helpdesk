addEventIE6(window,'load',inicializarEventos,false);

function inicializarEventos()
{
  var enlaces=document.getElementsByTagName('ul');
  for(f=0;f<enlaces.length;f++)
  {
    addEventIE6(enlaces[f],'click',presionBoton,false);
  }
}

function desactivar()
{
 var enlaces=document.getElementsByTagName('ul');
  for(f=0;f<enlaces.length;f++)
  {
    if (enlaces[f].parentNode.getAttribute('id')=='')
      enlaces[f].style.display='none';
  }
}

function presionBoton(e)
{
    desactivar();
    var ref=window.event.srcElement;
        if (ref.parentNode.childNodes[2]!=null)
           {ref.parentNode.childNodes[2].style.display='block';
           }
}

function addEventIE6(elemento,nomevento,funcion,captura)
{
  if (elemento.attachEvent)
  {
    elemento.attachEvent('on'+nomevento,funcion);
    return true;
  }
  else
    return false;
}
