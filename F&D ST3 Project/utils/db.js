API_URL = "https://dummyjson.com/products";

async function getProducts(){
    const response =await fetch(API_URL,{
        mode:"cors",
        headers: {
            'Access-Control-Allow-Origin':'*'
          }
    });
    return await response.json();
}
