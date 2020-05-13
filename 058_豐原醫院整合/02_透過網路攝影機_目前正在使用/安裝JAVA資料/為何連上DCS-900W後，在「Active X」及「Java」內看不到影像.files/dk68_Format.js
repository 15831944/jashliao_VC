var agt=navigator.userAgent.toLowerCase();
var appVer = navigator.appVersion.toLowerCase();
var is_mac = (agt.indexOf("mac")!=-1);
var is_minor = parseFloat(appVer);
var is_major = parseInt(is_minor);
var is_opera = (agt.indexOf("opera") != -1);
var iePos  = appVer.indexOf('msie');
var is_mac_ie = false;
if (iePos !=-1) {
   is_minor = parseFloat(appVer.substring(iePos+5,appVer.indexOf(';',iePos)));
   is_major = parseInt(is_minor);
}
var is_ie = ((iePos!=-1) && (!is_opera));
if (is_mac && is_ie) {
	is_mac_ie = true;
}
var is_ie5up = (is_ie && is_minor >= 5);
var is_ie5_5up =(is_ie && is_minor >= 5.5);
var is_safari = ((agt.indexOf('safari')!=-1)&&(agt.indexOf('mac')!=-1))?true:false;
var nn4 = false;
if (document.layers) {
	nn4 = true;
}



// menu style vars
var width = 125;
var height = 18;
var border = "#4f5a5b";
var menubgOn = "#8d9497";
var menubgOff = "#8d9497";

var menuXoffset = 0;
var menuYoffset = 1;

// functionality variables
var delay = 500;
var delayStart = 250;
var useMask = false;
var useDHTML = false;
var hideSels = false;
var start;
var hideFlag;
var hideTimer;
var showTimer;
var curMenu;
var curItem;
var curNav;
var activeMenu;
var theMenu;
var theImg;
var thePos;
var theDiv;
var theCont;
var theTable;
var theMask;
var onMenu = false;
var menusWritten = false;


// menu building variables;
var menucount = 0;

var menustyle = "padding:2px 2px 2px 5px; width:" + width + "px; text-align:left; border-left:#ffffff 1px solid; border-right:" + border + " 1px solid; background-color:" + menubgOff + "; cursor: hand;"
var menustyle2 = "padding:2px 2px 2px 5px; width:180px; text-align:left; border-left:#ffffff 1px solid; border-right:" + border + " 1px solid; background-color:" + menubgOff + "; cursor: hand;"

var separator = "";

function menuobject (label, url,target) {
    this.label = label;
    this.url = url;
    this.target = target;
    return this;
}

function renderdata () {
    menuData[catCount++] = tmpData;
    tmpData = new Array();
    count = 0;
}

// Turn iFrame mask on for IE 5.5+ / PC only
if (is_ie && !is_mac_ie) {
    if (is_ie5_5up) {
        useMask = true;
    }
    else {
        hideSels = true;
    }
}

// Turn on DHTML for 5+ browsers only
if (is_ie && !is_ie5up) {
    useDHTML = false;
} else if(!nn4) { useDHTML = true; }

function writeMenus() {
    if(useDHTML) {
        for (i = 0; i < menuData.length; i++) {
	    if ((i==0)&&(unDLinkSW)) menustyle_=menustyle2; else menustyle_=menustyle;
            document.writeln("<div id=\"menu" + i + "\" style=\"position:absolute; z-index:100; top:0px; left:0px; visibility:hidden;\">");
            if (useMask) {
                document.writeln("<table id=\"table" + i + "\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\"><tr><td>");
            }
            for (j = 0; j < menuData[i].length; j++) {
                if (j == 0) {
			document.write("<div id=\"menuitem" + menucount + "\" onMouseOver=\"startShow('" + i + "'); changebg('menuitem" + menucount + "'); changeStatus('" + menuData[i][j].url + "');\" onMouseOut=\"startHide(); changeStatus('');\" style=\"" + menustyle_ + "\"><div><a"+ menuData[i][j].target +" href=\"" + menuData[i][j].url + "\" class=\"topNavWhite\">" + menuData[i][j].label + "</a></div>" + separator + "</div>");
                }
                else if (j < menuData[i].length - 1) {
                    document.write("<div id=\"menuitem" + menucount + "\" onMouseOver=\"startShow('" + i + "'); changebg('menuitem" + menucount + "'); changeStatus('" + menuData[i][j].url + "');\" onMouseOut=\"startHide(); changeStatus('');\" style=\"" + menustyle_ + "\"><div><a"+ menuData[i][j].target +" href=\"" + menuData[i][j].url + "\" class=\"topNavWhite\">" + menuData[i][j].label + "</a></div>" + separator + "</div>");
                }
                else {
                    document.write("<div id=\"menuitem" + menucount + "\" onMouseOver=\"startShow('" + i + "'); changebg('menuitem" + menucount + "'); changeStatus('" + menuData[i][j].url + "');\" onMouseOut=\"startHide(); changeStatus('');\" style=\"" + menustyle_ + "border-bottom:" + border + " 1px solid;\"><div><a"+ menuData[i][j].target +" href=\"" + menuData[i][j].url + "\" class=\"topNavWhite\">" + menuData[i][j].label + "</a></div></div>");
                }
                menucount++;
            }
            if (useMask) {
                document.writeln("</td></tr></table>");
            }
            document.writeln("</div>");
            moveMenu(i);
        }
    }
    menusWritten = true;

}

function moveMenu(num) {
    tmpMenu = "menu" + num;
    thePos = getObj("pos" + num);
    theImg = "nav" + num;
    xPos = offsetLeft(thePos) + menuXoffset;
    yPos = offsetTop(thePos) + height + menuYoffset;

    getObj(tmpMenu).style.left = xPos;
    getObj(tmpMenu).style.top = yPos;
}


function showMenus() {
		unfocus();
    if (hideSels) {
        hideSelect();
    }
    onMenu = true;
    theMenu = "menu" + curMenu;
    activeMenu = theMenu;
    moveMenu(curMenu);
    if (useMask) {
        theMask = getObj("iMask");
        theTable = "table" + curMenu;
        theMask.style.left = xPos;
        theMask.style.top = yPos;
        theMask.style.width = getObj(theTable).offsetWidth;
        theMask.style.height = getObj(theTable).offsetHeight;
    }
    getObj(theMenu).style.visibility = "visible";
}


function startShow(menu) {
    curNav = menu;
    if (menusWritten && !nn4) {
        curMenu = menu;
        if (activeMenu) {
            getObj(activeMenu).style.visibility = "hidden";
        }
        clearTimer();
        if (!onMenu) {
            if (curItem) {
                curItem.style.backgroundColor = menubgOff;
            }
            showTimer = setTimeout("showMenus()", delayStart);
        }
        else {
            showMenus();
        }
    }
    else {
        return false;
   }
}


function startHide() {
    if (!onMenu) {
        if (curNav) {
            curNav = null;
        }
    }
    if (menusWritten && !nn4) {
        if (showTimer) clearTimeout(showTimer);
        start = new Date();
        hideFlag = true;
        hideTimer = setTimeout("hideMenus()", delay);
    }
    else {
        return false;
    }
}


function clearTimer() {
    if (hideTimer) clearTimeout(hideTimer);
    hideTimer = null;
    hideFlag = false;
}


function hideMenus() {
    if (!hideFlag) return;
    var elapsed = new Date() - start;
    if (elapsed < delay) {
        hideTimer = setTimeout("hideMenus()", delay - elapsed);
        return;
    }
    hideFlag = false;
    hideAllMenus();
    if (hideSels) {
        showSelect();
    }
}

function hideAllMenus() {
    changeStatus('');
    if (curNav) {
        curNav = null;
    }
    
    if (menuData) {
      for (i = 0; i<menuData.length; i++) {
        theMenu = "menu" + i;
        var menuObject = getObj(theMenu);
        if (menuObject) {
          menuObject.style.visibility = "hidden";
        }
      }
    }
    
    if (useMask) {
        if (theMask) {
            theMask.style.left = -300;
            theMask.style.top = -300;
        }
    }
    if (curItem) {
        curItem.style.backgroundColor = menubgOff;
    }
    onMenu = false;
}

function goTo(url) {
    document.location.href = url;
}

//return [object]
function getObj(theId) {
    if (document.getElementById) {
        theObj = document.getElementById(theId); 
    } else if (document.all) { 
        theObj = document.all[theId];
    }
    return theObj;
}

//Mac IE offset fix
function offsetLeft(o){
    var i = 0;
    while (o.offsetParent!=null) {
        i += o.offsetLeft;
        o = o.offsetParent;
    }
    return i + o.offsetLeft;
}

function offsetTop(o){
    var i = 0;
    while (o.offsetParent!=null) {
        i += o.offsetTop;
        o = o.offsetParent;
    }
    return i + o.offsetTop;
}

function changebg(id) {
    if (useDHTML) {
        var tmp = getObj(id);
        if (curItem) {
            if (tmp != curItem) {
                curItem.style.backgroundColor = menubgOff;
                tmp.style.backgroundColor = menubgOn;
            }
        } else { tmp.style.backgroundColor = menubgOn; }
        curItem = tmp;
    }
}

function unfocus() {
    for (x = 0; x < document.forms.length; x++) {
        for (y = 0; y < document.forms[x].elements.length; y++) {
            if (document.forms[x].elements[y].type == "text") {
                document.forms[x].elements[y].blur();
            }
        }
    }
}

function hideSelect() {
    var f = document.forms;
    for(var i=0;i<f.length;i++) {
        for (var j=0; j<f[i].elements.length; j++) {
            if (f[i].elements[j].type == 'select-one') {
                f[i].elements[j].style.visibility = 'hidden';
            }
        }
    }
}

function showSelect() {
    var f = document.forms;
    for(var i=0;i<f.length;i++) {
        for (var j=0; j<f[i].elements.length; j++) {
            if (f[i].elements[j].type == 'select-one') {
                f[i].elements[j].style.visibility = 'visible';
            }
        }
    }
}

function changeStatus(text) {
    window.status = text;
}

function clearbg() {
    if (curItem) {
        curItem.style.backgroundColor = menubgOff;
    }
    curItem = null;
}

if (document.addEventListener) {
    document.addEventListener("mouseup", mouseUp, false);
}

document.onmouseup = mouseUp;

function mouseUp() {
    hideAllMenus();
    return true;
}

function openModel(ModelObj){
	ModelSno=ModelObj.options[ModelObj.selectedIndex].value;
	location.href='/product_view.asp?sno='+ModelSno
}

function shfull(){
	obj=document.form1
	if (obj.search_full.value==''){
		alert('\n�п�J�n�j�M������r!�@�@�@�@�@�@\n');
	}
	else{
		obj.action='/asp/search.asp';
		obj.submit();
	}
}

function addeMail(){
	obj=document.form1
	if ((obj.emailAccount.value=='')||(obj.emailAccount.value=='�п�Je-Mail')) {alert('\n�п�Je-Mail!!�@�@�@�@�@�@\n')}
	else	{
			if (check_mail(obj.emailAccount.value)) {obj.action='/asp/NewsEmailAdd.asp';obj.target='_top';obj.submit()}
		}
}
function dfa(url){document.form1.action=url}
document.write ("<script language=javascript src=/js/z_checkEmail.js></script>")

var count = 0;
var catCount = 0;
var tmpData = new Array();
var menuData = new Array();
if (unDLinkSW){
	for (i = 0; i < unDLinkSolution.length; i++){
		tmpData[count++] = new menuobject(unDLinkSolution[i][0], unDLinkSolution[i][1],"");
	}
}
else{
	tmpData[count++] = new menuobject("�Ҧ����~", "/product.asp","");
	tmpData[count++] = new menuobject("�a�x����", "/solution_1.asp","");
	tmpData[count++] = new menuobject("���~����", "/solution_2.asp","");
	tmpData[count++] = new menuobject("���Q�n�I�ӫ~", "/solutionZ_c.asp","");
	tmpData[count++] = new menuobject("�N�z�~�P�M��", "/unBrand.asp","");
	tmpData[count++] = new menuobject("���H������", "http://www.dlinktw.com.tw/ctc_home.asp","");
	tmpData[count++] = new menuobject("D-Link Live", "http://dcs.dlinktw.com.tw/","");
	tmpData[count++] = new menuobject("My D-Link", "https://www.mydlink.com/","");
	tmpData[count++] = new menuobject("���\�ר�", "http://www.dlink.com/business/casestudies.asp"," target=_blank");
}
renderdata();

tmpData[count++] = new menuobject("���~�@����", "/support/product_all.asp","");
tmpData[count++] = new menuobject("VIP�[�ȪA��", "/support/vip_home.asp","");
tmpData[count++] = new menuobject("�ɮפU��", "/support/download_home.asp","");
tmpData[count++] = new menuobject("�`�����D", "/support/faq_home.asp","");
tmpData[count++] = new menuobject("�޳N�Ը�", "/support/inquiry_home.asp","");
tmpData[count++] = new menuobject("���תA��", "/support/repairservice.asp","");
tmpData[count++] = new menuobject("D-Link���~�e��", "/support/repairapply_home.asp","");
tmpData[count++] = new menuobject("�N�z���~�e��", "/unrepairapply_home.asp","");
tmpData[count++] = new menuobject("�Ш|�V�m", "/support/train_list.asp","");
tmpData[count++] = new menuobject("�M�ק޳N�䴩", "/support/pj_home.asp","");
renderdata();

tmpData[count++] = new menuobject("����A�Ȥ���", "wheretobuy_hq.asp","");
tmpData[count++] = new menuobject("���پP�����", "/wheretobuy_list.asp","");
tmpData[count++] = new menuobject("���v�N�z��", "/wheretobuy_retail.asp","");
tmpData[count++] = new menuobject("�u�W�ʪ�", "/dshop/default.asp","");
tmpData[count++] = new menuobject("���H������", "http://www.dlinktw.com.tw/ctc_home.asp","");
tmpData[count++] = new menuobject("�g�P�p��", "/partner","");
renderdata();

tmpData[count++] = new menuobject("�|�����߭���", "/member/default.asp","");
tmpData[count++] = new menuobject("�|�����", "/member/member.asp","");
tmpData[count++] = new menuobject("�|���P���Q��k", "/member/bonus.asp","");
tmpData[count++] = new menuobject("�ڪ����~", "/member/product.asp","");
tmpData[count++] = new menuobject("�|������", "/member/memberEvents.asp","");
renderdata();

tmpData[count++] = new menuobject("����ڭ�", "/about.asp","");
tmpData[count++] = new menuobject("�~�P�G��", "/brand.asp","");
tmpData[count++] = new menuobject("���H�M��", "http://www.corpasia.net/taiwan/2332/irwebsite_c/index.php?version=c"," target=_blank");
tmpData[count++] = new menuobject("���y�G��", "http://www.dlink.com/corporate/international.asp"," target=_blank");
tmpData[count++] = new menuobject("���v�u��", "/history.asp","");
tmpData[count++] = new menuobject("�~�׳��i", "http://www.dlink.com/corporate/annualReports/"," target=_blank");
tmpData[count++] = new menuobject("�̷s¾��", "http://www.104.com.tw/jobbank/cust_job/introduce.cfm?jobsource=checkc&invoice=22099189000&page=1"," target=_blank");
tmpData[count++] = new menuobject("���p�v�F��", "http://www.dlink.com/corporate/employ"," target=_blank");
tmpData[count++] = new menuobject("�p���ڭ�", "/contactus.asp","");
renderdata();

tmpData[count++] = new menuobject("�ͰT�x�W","/ctc_home.asp","")
tmpData[count++] = new menuobject("���H�����~","/ctc_product.asp","")
tmpData[count++] = new menuobject("���H������","/ctc_events.asp","")
tmpData[count++] = new menuobject("���תA��","/ctc_service.asp","")
tmpData[count++] = new menuobject("�Ш|�V�m","/ctc_train_list.asp","")
tmpData[count++] = new menuobject("���H�����U��","/ctc_download.asp","")
tmpData[count++] = new menuobject("�t�X�t��","/ctc_dealer.asp","")
//tmpData[count++] = new menuobject("���\�ר�","/ctc_story.asp","")//
tmpData[count++] = new menuobject("�w�˪A�ȥӽ�","/ctc_setupApply.asp","")
renderdata();

