/+  name-search
:-  %say
|=  [^ [tag=tape ~] lim=_3]
:-  %tang
^-  tang
=+  res=(run:name-search lim tag)
=+  kes=`(list @ud)`(sort ~(tap in ~(key by res)) gth)
|-  ^-  tang
?~  kes  ~
=/  mas
  %+  sort  `(list tape)`~(tap in `(set tape)`(~(got by res) i.kes))
  |=  [a=tape b=tape]  ^-  bean
  ?~  b  &
  ?~  a  |
  &(!(gth i.a i.b) $(a t.a, b t.b))
%+  weld
  (turn mas |=(mat=tape (crip "{(scow %ud i.kes)}: {mat}")))
$(kes t.kes)
