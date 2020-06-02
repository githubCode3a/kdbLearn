import requests
if __name__=='__main__':
	url = "{{API_URL}}"

	payload = "{}"
	headers = {
	    'x-rapidapi-key': "{{API_KEY}}",
	}
	params = {

	}

	response = requests.request("{{HTTP_METHOD}}", url, data=payload, headers=headers, params=params)

	print(response.text)