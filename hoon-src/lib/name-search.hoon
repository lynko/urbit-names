=+  =<  [sis=(separate sis:po) dex=(separate dex:po)]
    |%
      ++  separate
        |=  [syl=cord]  ^-  (list tape)
        ?:  =('' syl)  ~
        [(trip (end [3 3] syl)) $(syl (rsh [3 3] syl))]
    --
|_  [lim=atom]
  +$  dist  atom
  +$  stat
    $:  rem=tape
        mat=tape
        las=(unit char)
        lap=(unit char)
    ==
  +$  band  (jug dist stat)
  +$  wave  (list (pair dist stat))
  +$  ring  (pair band band)
  ++  init
    |=  [tag=tape]  ^-  ring
    =+  ban=(~(put ju *band) 0 %*(. *stat rem tag))
    [ban ban]
  ++  run
    |=  [lim=dist tag=tape]
    =.  ^lim  lim
    %.  |=(sas=(set stat) (~(run in sas) |=(sat=stat (flop mat.sat))))
    %~  run  by
    =+  [dun=*band rin=(init tag)]
    |-  ^-  _dun
    ?:  &(=(~ p.rin) =(~ q.rin))  dun
    =/  [den=wave ren=ring]  (walk rin)
    $(dun (~(gas ju dun) den), rin ren)
  ++  walk
    |=  [rin=ring]  ^-  (pair wave ring)
    =/  [dul=wave lep=wave byl=band]  (step p.rin dex)
    =/  [dur=wave rep=wave byr=band]  (step q.rin sis)
    :+  (weld dul dur)
      (~(gas ju byl) rep)
    (~(gas ju byr) lep)
  ++  step
    |=  [ban=band aff=(list tape)]  ^-  (trel wave wave band)
    =/  [wav=wave byn=band]  (bott ban)
    =+  res=(skid wav |=([dis=dist sat=stat] =(~ rem.sat)))
    =.  +.res  (skim `wave`+.res |=([dis=dist sat=stat] (lte dis lim)))
    :+  -.res
      %-  zing
      %+  turn  aff
      |=  [syl=tape]  ^-  wave
      %-  zing
      ^-  (list wave)
      %+  turn  `wave`+.res
      |=  [dis=dist sat=stat]  ^-  wave
      (try syl dis sat)
    byn
  ++  bott
    |=  [ban=band]  ^-  (pair wave band)
    =+  kes=(sort ~(tap in ~(key by ban)) lth)
    ?~  kes  *(pair wave band)
    =+  dis=i.kes
    =+  sas=(~(got by ban) dis)
    :-  (turn ~(tap in sas) |=(sat=stat [dis sat]))
    (~(del by ban) dis)
  ++  try
    |=  [syl=tape dis=dist sat=stat]  ^-  wave
    =+  upp=(add dis 6)
    %-  turn
    :_  |=([sat=stat dis=dist] [dis sat])
    %~  tap  by
    %-  roll
    :_  |=  [[dis=dist sat=stat] mip=(map stat dist)]
        =+  hav=(~(get by mip) sat)
        ?.  ?&  (lte dis lim)
                (lth dis upp)
                |(?=(~ hav) (lth dis u.hav))
            ==
          mip
        (~(put by mip) sat dis)
    |-  ^-  wave
    ?~  syl
      ?~  rem.sat  [dis sat]~
      :+  [dis sat]
        [(add dis (lent rem.sat)) sat(rem "", las `i.rem.sat, lap ~)]
      ~
    ?~  rem.sat
      :-  :-  (add dis (lent syl))
          sat(mat (weld (flop syl) mat.sat), las ~, lap `(rear syl))
      ~
    ;:  weld
      ?.  =(i.rem.sat i.syl)  ~
      %=  $
        rem.sat  t.rem.sat
        mat.sat  [i.syl mat.sat]
        las.sat  `i.rem.sat
        lap.sat  `i.rem.sat
        syl      t.syl
      ==
    ::
      ?.  |(=(`i.rem.sat las.sat) =(`i.rem.sat lap.sat))  ~
      %=  $
        dis      +(dis)
        rem.sat  t.rem.sat
        las.sat  ~
        lap.sat  ~
      ==
    ::
      ?:  |(?=(~ mat.sat) !=(i.mat.sat i.syl))  ~
      %=  $
        dis      +(dis)
        mat.sat  [i.syl mat.sat]
        las.sat  ~
        lap.sat  ~
        syl      t.syl
      ==
    ::
      ?.  =(i.syl 'y')  ~
      =+  hig=(high rem.sat)
      ?~  hig  ~
      %=  $
        dis      +(dis)
        rem.sat  u.hig
        mat.sat  [i.syl mat.sat]
        las.sat  ~
        lap.sat  ~
        syl      t.syl
      ==
    ::
      $(rem.sat t.rem.sat, las.sat `i.rem.sat, lap.sat ~, dis +(+(dis)))
    ::
      $(syl t.syl, mat.sat [i.syl mat.sat], las.sat ~, lap.sat `i.syl, dis +(+(dis)))
    ==
  ++  high
    |=  [rem=tape]  ^-  (unit tape)
    ?:(?=([%i %g %h *] rem) `t.t.t.rem ~)
--
