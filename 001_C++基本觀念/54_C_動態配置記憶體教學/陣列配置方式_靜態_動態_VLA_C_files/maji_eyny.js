if("undefined"==typeof SD||!SD)var SD={};SD.config={adhost:"http://ysm.sitemaji.com/",statichost:"http://ad.sitemaji.com/",hosthash:"389a71ddd068",sitename:"eyny"};
(function(){SD.util=SD.util||{};S=SD.util;SD.util.Dom={_reClassNameCache:{},_getClassRegEx:function(b){var a=S.Dom._reClassNameCache[b];a||(a=RegExp("(?:^|\\s+)"+b+"(?:\\s+|$)"),S.Dom._reClassNameCache[b]=a);return a},getElementsByClassName:function(b,a,c,e){for(var d=[],a=(c||document).getElementsByTagName(a||"*"),b=S.Dom._getClassRegEx(b),c=0,g=a.length;c<g;c++)b.test(a[c].className)&&(d[d.length]=a[c],e&&e.call(a[c],a[c]));return d},hasClass:function(b,a){if("undefined"==typeof b||null==b||!RegExp)return!1;
var c=RegExp("(^|\\s)"+a+"(\\s|$)");return"string"==typeof b?c.test(b):"object"==typeof b&&b.className?c.test(b.className):!1},getAncestorByTagName:function(b,a){for(;b=b.parentNode;)if(b.tagName.toLowerCase()==a)return b;return null}};SD.util.Event={getTarget:function(b){return this.resolveTextNode(b.target||b.srcElement)},resolveTextNode:function(b){try{if(b&&3==b.nodeType)return b.parentNode}catch(a){}return b},preventDefault:function(b){b.preventDefault?b.preventDefault():b.returnValue=!1}}})();
(function(){var b=SD.util.Dom;SD.util.createEl={get:function(a,b,e){var a=document.createElement(a),d;for(d in b)a[d]=b[d];if(e)a.innerHTML=e;this.append(a);return a},append:function(a){(document.getElementsByTagName("head")[0]||document.body).appendChild(a)},remove:function(a){setTimeout(function(){a.parentNode.removeChild(a);a=null},0)},js:function(a,b){var e=this.get("script",{src:a,type:"text/javascript"},null);b&&e.setAttribute("charset",b);return e},css:function(a,b){b||(b="all");return this.get("link",
{href:a,rel:"stylesheet",type:"text/css",media:b},null,"head")},adtemplate:function(a,c,e){c.className=c.className||SD.config.prefix;document.write('<div class="'+c.className+'" style="display:none;"></div>');a=b.getElementsByClassName(c.className);a=a[a.length-1];if(e)a.innerHTML=e;return a}}})();
(function(){var b=SD.util.Dom.getElementsByClassName("sitemajicustom");SD.ysm={swfHTML:function(a,b,e){return sHtml='<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" width="'+b+'" height="'+e+'" id="sitemajisystem"><param name="movie" value="'+decodeURIComponent(a)+'"><param name="allowScriptAccess" value="always"><param name="wmode" value="transparent"><embed wmode="transparent" src="'+decodeURIComponent(a)+'" width="'+b+'" height="'+e+'" allowscriptaccess="always"></embed></object>'},
getSitemajiad:function(a){for(var c=0,e=b.length;c<e;c++){var d="",g="",f=b[c],d=f.getAttribute("model")?f.getAttribute("model"):"300x250";sSize="s"+d;var h=d.split("x"),g=h[0]?h[0]:"300",h=h[1]?h[1]:"250";if(a[sSize].ad_size==d&&""!==a[sSize].ad_list[0].ad_type)d=a[sSize].ad_list[0].ad_type,g="img"==d?'<a href="'+decodeURIComponent(a[sSize].ad_list[0].ad_url)+'" target="_blank"><img style="margin:0 auto;display:block;width:'+g+"px;height:"+h+'px;" src="'+decodeURIComponent(a[sSize].ad_list[0].ad_img)+
'"></a>':SD.ysm.swfHTML(decodeURIComponent(a[sSize].ad_list[0].ad_img),g,h),f.innerHTML=g,a[sSize].ad_list.shift()}},percent:function(a){var c={"300x250":1,"728x90":2,"300x100":3,"240x400":4,"120x120":5,"160x600":6,"425x300":7,"425x600":8,"234x60":9,"120x600":10},e={};if(Math.floor(101*Math.random())<a){for(var d="",a=0,g=b.length;a<g;a++){var f=b[a],f=f.getAttribute("model")?f.getAttribute("model"):"300x250";e[c[f]]=void 0==e[c[f]]?1:e[c[f]]+1}for(var h in e)d=d+h+"x"+e[h]+",";d=d.replace(RegExp("[,]+$",
"g"),"");SD.util.createEl.js("http://rd.sitemaji.com/ask.php?size="+d+"&hosthash="+SD.config.hosthash+"&callback=SD.ysm.getSitemajiad")}else{a=0;for(g=b.length;a<g;a++){f=b[a];c=f.innerHTML;try{d=c.replace(/^\s+|\s+$/g,"")}catch(i){d=c}""==d&&(f=f.getAttribute("model")?f.getAttribute("model"):"300x250",f.split("x"))}}},drgen:function(){b[0]&&SD.ysm.percent(100)}}})();(function(){SD.util.Dom.getElementsByClassName("sitemajicustom")[0]&&SD.ysm.drgen()})();
