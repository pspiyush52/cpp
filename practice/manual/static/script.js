$("#nav-bar").css("display", "none")

$("div.side-button").on("click", () => {
    $("#nav-bar").slideToggle(200);
    $("#nav-bar").css({
        opacity: "100%"
    });
});