function shortenURL(){
    let url=document.getElementById("url");
    fetch("/shorten",{
        method: "POST",
        headers:{"Content-Type": "application/x-www-form-urlencoded"},
        body: `url=${encodeURIComponent(url)}`
    })
    .then(response => response.text())
    .then(result => document.getElementById("result").innerHTML = result)
    .catch(err => console.error(err));
}