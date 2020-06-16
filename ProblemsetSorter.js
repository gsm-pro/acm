// For http://acm.sgu.ru/olimp/problemset.php & http://acm.sgu.ru/univer/problemset.php
var tb = document.querySelector("table table table[width='95%'] tbody");
var threshold = 559;
[...tb.querySelectorAll("tr+tr")].sort((x, y) => (y.cells[0].textContent <= threshold) - (x.cells[0].textContent <= threshold) || (1+y.cells[2].textContent) - (1+x.cells[2].textContent) || x.cells[0].textContent - y.cells[0].textContent).forEach(tr => tb.appendChild(tr));
document.head.innerHTML += "<style>.st0:nth-child(odd),.st1:nth-child(odd){background:#F3F8FF}.st0:nth-child(even),.st1:nth-child(even){background:#E0E5EF}.st0:hover,.st1:hover{background:antiquewhite}</style>";0