function _uCount(type,callback){if("undefined"==typeof type){type=_type}if("undefined"==typeof callback){callback=function(){return}}var i;var _image_src="http://pixanalytics.com/pa.gif";var _userdata="&ver=1.0&random="+Math.random();var _pix=pix||{};var _attr=new Array("document.referrer","document.URL","screen.availHeight","screen.availLeft","screen.availTop","screen.availWidth","screen.colorDepth","screen.height","screen.pixelDepth","screen.width","window.closed","window.height","window.innerHeight","window.innerWidth","window.length","window.location","window.pageXOffset","window.pageYOffset","window.outerHeight","window.outerWidth","window.screenX","window.screenY","window.width","navigator.userAgent","window.devicePixelRatio","_pix.login_name","_pix.owner","_pix.visitor","_pix.openid");for(i=0;i<_attr.length;i++){_userdata+="&"+_attr[i]+"="+encodeURI(eval(_attr[i]))}if(type!==undefined&&type){i=new Image(1,1);i.src=_image_src+"?"+"t="+type+_userdata;i.onerror=i.onabort=i.onload=callback}}