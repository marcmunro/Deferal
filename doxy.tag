<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.1">
  <compound kind="file">
    <name>Deferal.cpp</name>
    <path>/home/marc/proj/bloodnok-marine/digital_engine_panel/mypanel/Deferal/</path>
    <filename>Deferal_8cpp.html</filename>
    <includes id="Deferal_8h" name="Deferal.h" local="yes" imported="no">Deferal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>INTEGER</name>
      <anchorfile>Deferal_8cpp.html</anchorfile>
      <anchor>a91d43eadec33c80149f92e5abf5df58c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>ulo_cmp</name>
      <anchorfile>Deferal_8cpp.html</anchorfile>
      <anchor>af960118b1e0d62e764a3da78e08b9a32</anchor>
      <arglist>(unsigned long x, unsigned long y)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Deferal.h</name>
    <path>/home/marc/proj/bloodnok-marine/digital_engine_panel/mypanel/Deferal/</path>
    <filename>Deferal_8h.html</filename>
    <class kind="class">Deferal</class>
    <member kind="define">
      <type>#define</type>
      <name>ONE_SECOND_MS</name>
      <anchorfile>Deferal_8h.html</anchorfile>
      <anchor>a3e2114602b9038c31781c41f246b837e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>PostDeferalFn</name>
      <anchorfile>Deferal_8h.html</anchorfile>
      <anchor>a4b6f2626effdd9a4a02842a3bf362fa2</anchor>
      <arglist>)(void *)</arglist>
    </member>
    <member kind="typedef">
      <type>unsigned long(*</type>
      <name>TimerFn</name>
      <anchorfile>Deferal_8h.html</anchorfile>
      <anchor>ab85bcb2e77d63963303c21ff09e6ab43</anchor>
      <arglist>)()</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>deferal_status_t</name>
      <anchorfile>Deferal_8h.html</anchorfile>
      <anchor>a75c2ed385ecc4230ed2dc8a2dfec8182</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEFERAL_RUNNING</name>
      <anchorfile>Deferal_8h.html</anchorfile>
      <anchor>a75c2ed385ecc4230ed2dc8a2dfec8182a707dbf90a7792d6e8890308a51fc9bd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEFERAL_PAUSED</name>
      <anchorfile>Deferal_8h.html</anchorfile>
      <anchor>a75c2ed385ecc4230ed2dc8a2dfec8182a1c389c435319ee932b03ae339d2666c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEFERAL_STOPPED</name>
      <anchorfile>Deferal_8h.html</anchorfile>
      <anchor>a75c2ed385ecc4230ed2dc8a2dfec8182a844b6527499d834d466c33dd8efb0d25</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>README.md</name>
    <path>/home/marc/proj/bloodnok-marine/digital_engine_panel/mypanel/Deferal/docs/</path>
    <filename>README_8md.html</filename>
  </compound>
  <compound kind="class">
    <name>Deferal</name>
    <filename>classDeferal.html</filename>
    <member kind="function">
      <type></type>
      <name>Deferal</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a6b3777e990293e9e3e2521dbb1afe76a</anchor>
      <arglist>(unsigned long delay, bool autorepeat=false, bool start=true, TimerFn timer_fn=millis)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Deferal</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a89040d4bfdb9d3b927f9bd892e824e36</anchor>
      <arglist>(unsigned long delay, PostDeferalFn fn, void *param=NULL, bool autorepeat=false, bool start=true, TimerFn timer_fn=millis)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Deferal</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a1359199cc03b97aaa34976cb4bd83b66</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>start</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>ad0bfe1cc65f7009cc5175136740bc662</anchor>
      <arglist>(unsigned long delay=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a1b35cf239dfc68b5fecb067dab6cb1f9</anchor>
      <arglist>(bool run_post_fn=true, bool allow_repeat=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pause</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a7bb15b4958d45dc63ca9c4bab43392c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resume</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>aa7b32daac51332934c0478f61fcc3fad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>stopped</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a0552be7d0fd3aebee199cb53b508d57a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>paused</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>ad837ef00d742e0844b1ddb4e4b13bc26</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>running</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>adcab9733fd6f5794a19fe2bb76d9896c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>remaining</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a69644e7eff30736828c5108f8810de51</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>delayPeriod</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a69c868ff56793d880a72805b51ef8286</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>deferal_status_t</type>
      <name>status</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a615ca81b48d77c6ba6cc2ad40257a5dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>again</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a7ee6d3af75ddcf206dbde9cc5abe83f5</anchor>
      <arglist>(unsigned long delay=0, bool run_post_fn=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDeferalFn</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a5b78a5fcdbe57028bcbd886fe163412b</anchor>
      <arglist>(PostDeferalFn fn, void *param=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDelay</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a7739fed5fa8017ac1c5448ac7f645f2e</anchor>
      <arglist>(unsigned long delay)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Deferal *</type>
      <name>checkDeferals</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a83c5736c8313fc8ff07b8c6fe40cbde9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>init</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>acae709218afc3492f3e47e0c0690758f</anchor>
      <arglist>(unsigned long delay, bool autorepeat, bool start, TimerFn timer_fn)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>updateStatus</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>ad094b6527fbdb4be62f5cb1176dbc79c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>addDeferalEntry</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>aff8bf1fd239b4b738591da76ac1bd2f2</anchor>
      <arglist>(Deferal *entry)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>removeDeferalEntry</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>ae1ac75c9a504aebd9e33041110abf5df</anchor>
      <arglist>(Deferal *to_remove)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>autorepeat_</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>ab6df4c55d6eaa3d75913ae9b665788ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned long</type>
      <name>start_time_</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>acc9c952bdf3f21ece04fb779fd82247e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned long</type>
      <name>delay_time_</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a20a98e7cc583056aa243cd97768359cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned long</type>
      <name>remaining_time_</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>ab52099652bf8cf5e64101efd8c38d957</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>deferal_status_t</type>
      <name>status_</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a0300ff523c1ceaeea25a192e9e9f1b07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PostDeferalFn</type>
      <name>defer_fn_</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>aac1719a479ef020334b8ffd60d620bcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>void *</type>
      <name>defer_fn_param_</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a6a7501a2a266bdd8cfe7e51ac7ccfe28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>TimerFn</type>
      <name>timer_fn_</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>aa44c804b1c5509a37aa192066c76fb13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Deferal *</type>
      <name>next_</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>aae4abc063acc9733b77e177177a86b00</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static Deferal *</type>
      <name>deferal_list_</name>
      <anchorfile>classDeferal.html</anchorfile>
      <anchor>a1107aed2453f0f4ffd123750c3985bd0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Deferal - Versatile Non blocking Delays and Deferred Execution</title>
    <filename>index.html</filename>
    <docanchor file="index.html">md_docs_README</docanchor>
  </compound>
</tagfile>
