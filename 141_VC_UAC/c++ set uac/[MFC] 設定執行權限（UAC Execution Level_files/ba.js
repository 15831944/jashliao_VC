﻿var BA_FUNC_EXTENTION={ex:true,sTL:'BloggerAds%20%E5%BB%A3%E5%91%8A',sAM:'%E6%9B%B4%E5%A4%9A%E8%A8%8A%E6%81%AF..',sAO:'i',sAU:'o',sAC:'ck',sCN:'class',sHF:'href',sTG:'target',sBL:'_blank',sWT:'width',sHT:'height',sBC:'#FFF',sBCO:'#FFFFE0',sPX:'px',sASA:'allowScriptAccess',sQLT:'quality',sWM:'wmode',sFVS:'flashvars',sALG:'align',sUD:'undefined',vBLI:-1,vBLT:0,vEL:5,vESL:60,vRD:1,sWB:'www.bloggerads.net',aAD:[],oT:null,rT:null,hT:null,vNO:true,eXT:function(t){t.dEC(this,function(a){t[a]=this==window?null:this;});},aEV:function(o,n,f){if(o.attachEvent){o.attachEvent('on'+n,f);}else{o.addEventListener(n,f,false);}},aA:function(afs){var t=this;t.dEC(afs,function(){this.el=t.vEL;this.i=t.aAD.length;t.aAD.push(this);});},iAry:function(o){return Object.prototype.toString.call(o)==="[object Array]";},iTD:function(ad){return/thirdparty/.test(ad.at)&&ad.fl&&ad.fl!='';},rA:function(afs){var t=this,ad,aa='';t.aA(afs);with(this){if(!(ad=aAD)||ad.length==0){return;}
aa+=gTS();dEC(ad,function(i){aa+='<ins class="ba_ad_panel">'+gADB(this,i)+'</ins>';});aa+=gFS();pAD(aa);setTimeout(function(){var m=t.sIM;if(t.iAry(m)){t.dEC(m,function(){t.dIM(this);});}else{t.dIM(m);}},t.sIMD);aEV(window,'load',function(){var ad=t.gAD();ad.onmouseover=function(){t.vNO=false;};ad.onmouseout=function(){t.vNO=true;};t.sRD();});}},gBL:function(){with(this){var i=sAE+'_bannerLeft',bl=gBI(i),ad=gAD();if(bl==null){sS(bl=gCE('int',{id:i}),{textDecoration:'none',display:'none',position:'absolute',background:'transparent'});ad.insertBefore(bl,ad.firstChild);}
return bl;}},oBL:function(e,ad){var tgr=this;with(this){var ob=gO(gAD()),os=gO(e),bl=gBL(),l,t;if(ad.fl==''){bl.innerHTML='';return;}
if(os.l-ad.wl<0){l=180;}else{l=-(ad.wl);}
t=os.t-ob.t;bl.onmouseover=function(){tgr.aC(this,tgr.vBLI,tgr.sAO);};bl.onmouseout=function(){tgr.aC(this,tgr.vBLI,tgr.sAU);};if(iTD(ad)){bl.innerHTML=tB('iframe',gKV({sWT:ad.wl,sHT:ad.hl,src:ad.fl+'?clickTAG='+eURI(ad.ct),frameborder:0,border:0,cellspacing:0,allowtransparency:true,scrolling:'no'}));}else{bl.innerHTML=gSWF(ad.fl,'getlink='+eURI(ad.ct),ad.wl,ad.hl);}
sS(bl,{marginLeft:l+sPX,marginTop:t+sPX,display:''});}},cBL:function(){with(this){var bl=gBL();bl.innerHTML='';sS(bl,'display','none');}},dIM:function(u){this.gCE('img',{src:u+'?c='+this.sAE},'');},sEP:function(){this.vBLT=new Date();},gRD:function(){return Math.ceil(Math.random()*1000);},dEP:function(ad){with(this){if(ad.el<1){return;}
ad.el-=1;var sec=Math.ceil((new Date()-vBLT)/1000);sec=sec>vEL?vEL:sec;gCE('img',{src:ad.et+['?s='+sec,'c='+sAE,'r='+gRD()].join('&')},'');}},aC:function(e,i,a){var t=this;with(t){var bad=gBI('ba_ad_'+i),ad=aAD[i],it=(/distent/.test(ad.at)||iTD(ad));if(a==sAO){sS(bad,'background',sBCO);if(oT!=null){cTM();if(vBLI!=i){dEP(aAD[vBLI]);vBLI=i;sEP();oBL(bad,ad);}}else{vBLI=i;if(it){sEP();oBL(bad,ad);}}
return;}
if(a==sAU){sS(bad,'background',sBC);if(it){oT=setTimeout(function(){with(t){vBLI=-1;dEP(ad);cBL();cTM();}},800);}
return;}
if(a==sAC){window.open(ad.ct);return false;}}},gO:function(o){var l=o.offsetLeft||0,t=o.offsetTop||0;if(o.offsetParent){while(o=o.offsetParent){l+=o.offsetLeft||0;t+=o.offsetTop||0;}}else{l+=o.x;t+=o.y;}
return{l:l,t:t};},gADB:function(ad,i){with(this){var bc='ba_ad_',rd,acf=function(a){return sAE+'.aC(this, '+i+', \''+a+'\')'},c=acf(sAC),t='ins';if(/picture|flash|distent/i.test(ad.at)){var pi=Math.random().toString().replace('.','');rd=tB(t,gKV({sCN:bc+'area',id:bc+i,onmouseover:acf(sAO),onmouseout:acf(sAU)}),tB(t,gKV({sCN:bc+'title',onclick:c}),dURI(ad.t))+tB(t,gKV({sCN:bc+'picture',id:bc+pi,onclick:c,style:'height:'+ad.h+'px'}))+tB(t,gKV({sCN:bc+'body',onclick:c}),dURI(ad.b))+(ad.iub=='1'?gAFB(ad):tB(t,gKV({sCN:bc+'more',onclick:c}),dURI(sAM))));setTimeout(function(){dEC(gBT('ins'),function(){if(this.id==bc+pi){var pic=/picture/i.test(ad.at);if(!pic&&/Firefox[\/\s](\d+\.\d+)/i.test(navigator.userAgent)){this.onclick='return false';}
this.innerHTML=gPS(ad.p,ad.ct,ad.w,ad.h,pic);}});},800);}else if(/thirdparty/.test(ad.at)){rd=tB(t,gKV({sCN:bc+'area',id:bc+i,onmouseover:acf(sAO),onmouseout:acf(sAU)}),tB('iframe',gKV({sWT:ad.w,sHT:ad.h,src:ad.p+'?clickTAG='+eURI(ad.ct),frameborder:0,border:0,cellspacing:0,allowtransparency:true,scrolling:'no'})));}
return rd;}},gPS:function(p,c,w,h,isp){with(this){if(isp){return'<img '+gKV({src:p,sWT:w,sHT:h,border:0})+'/>';}
return gSWF(p,'getlink='+eURI(c),w,h);}},gSWF:function(p,f,w,h){with(this){var sa='always',q='high',wm='transparent',ag='middle',pm=function(k,v){return tB('PARAM',gKV({NAME:k,VALUE:v}));};return tB('object',gKV({classid:'clsid:d27cdb6e-ae6d-11cf-96b8-444553540000',codebase:'http://fpdownload.adobe.com/pub/shockwave/cabs/flash/swflash.cab#version=8,0,0,0',sWT:w,sHT:h,sALG:ag}),pm(sASA,sa)+pm('movie',p)+pm(sQLT,q)+pm(sWM,wm)+pm(sFVS,f)+tB('embed',gKV({src:p,sFVS:f,sWT:w,sHT:h,sWM:wm,sQLT:q,sALG:ag,sASA:sa,type:'application/x-shockwave-flash',pluginspage:'http://adobe.com/go/getflashplayer'})));}},gKV:function(k,v){var ts=this;with(ts){if(arguments.length==2){return k+'="'+v+'" ';}else{var s='';dEC(k,function(ks){s+=gKV(/undefined/.test(ts[ks])?ks:ts[ks],this);});return s;}}},sS:function(o,s,v){with(this){if(v){sATT(o.style,s,v);return o;}
dEC(s,function(k){sATT(o.style,k,this);});}
return o;},gAFB:function(ad){with(this){return tB('ins',gKV('class','ba_ad_fb'),(ad.fbLik==''?'':gFL(ad.fbLik,ad.ct))+(ad.fbPub==''?'':gFP(ad.fbPub,ad.fbPubC))+(ad.fbCol==''?'':gFC(ad.fbCol,ad.fbColC)));}},gFL:function(l,ct){with(this){return tB('iframe',gKV({src:[sSC,sMD,['apps/fb_conn.htm?clickTAG='+eURI(ct),'fansTAG='+eURI(l),'v=2'].join('&')].join('/'),style:'border:none; overflow:hidden; width:75px; height:21px;float:left;margin-right:2px;',frameborder:0,border:0,cellspacing:0,allowtransparency:true,scrolling:'no'}));}},gFP:function(l,c){with(this){var cn='ba_ad_fb_pub';return tB('ins',gKV({sCN:cn,onclick:'window.open(\''+l+'\');'}),tB('ins',gKV(sCN,cn+'_inner'),c));}},gFC:function(l,c){with(this){var cn='ba_ad_fb_col';return tB('ins',gKV({sCN:cn,onclick:'window.open(\''+l+'\');'}),tB('ins',gKV(sCN,cn+'_inner'),c));}},gAA:function(){return this.gBI(this.sAE);},hO:function(){var t=this;with(t){hC();hT=setTimeout(function(){t.gCE('img',{src:t.hIM});},500);}},hC:function(){clearTimeout(this.hT);this.hT=null;},gTS:function(){with(this){return tB('ins','onmouseover="'+this.sAE+'.hO()" onmouseout="'+this.sAE+'.hC()" '+gKV({sCN:'ba_title',onclick:'window.open(\''+this.hCL+'\')'}),dURI(sTL));}},gFS:function(){with(this){return tB('ins',gKV({sCN:'ba_foot',onclick:'window.open(\''+this.hCL+'\')'}));;}},cTM:function(tm){clearTimeout(this.oT);this.oT=null;},dURI:function(s){return decodeURIComponent(s);},fD:function(e,io,f){if(e==null)
return;var t=this;(function ff(o,d){if(io?(o<0):(o>1)){if(typeof(f)!=t.sUD){f.apply(this);}
return;}
t.sS(e,{opacity:o,filter:'alpha(opacity='+(o*100)+')'});o+=(io?(-0.1):(+0.1));setTimeout(function(){ff(o,d)},d);})(io?1:0,100);},rAN:function(afs){var t=this,a=null,gbn=function(n,o){return(o||t.oD).getElementsByClassName(n);},adb=gbn('ba_ad_area',t.gAA()),i=0;(function n(){var ad=adb[i++];if((a=afs.pop())==null){return;}
t.fD(ad,true,function(){var p=ad?ad.parentNode:null,d=t.gCE('ins'),b=t.gAD();if(ad==null||p==null){return;}
if(typeof(a.i)==t.sUD){t.aA([a]);}
d.innerHTML=t.gADB(a,a.i);p.replaceChild(d.childNodes[0],ad);n();});})();t.vRD++;setTimeout(function(){var m=t.sIM;if(t.iAry(m)){t.dEC(m,function(){t.dIM(this);});}else{t.dIM(m);}
t.sRD();},t.sIMD);},sRD:function(){var t=this;clearTimeout(t.rT);if(t.sRDC==1)
return;t.rT=setTimeout(function(){if(t.vNO==false){t.sRD();return;}
with(t){if(sRDS&&(vRD<parseInt(sRDC))){lJS([sSC,sADD,sADP].join('/')+'?'+['blogid='+sBID,'fid='+sFID,'c='+sAE,'d='+sCD,'r='+eURI(eURI(sL)),'nd=1'].join('&'));}else{var s=(vRD%sRDC)*(aAD.length/sRDC);rAN(aAD.slice(s,s+(aAD.length/sRDC)));}}},t.sRDS*1000);}}