#ifndef UNIBITAPI_H
#define UNIBITAPI_H
using namespace concurrency::streams; 
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;


class UniBitapi{
	private:
		std::string ticker;
		std::string jsonStr;
	public:

	UniBitapi(char *ticker_){
		ticker = ticker_;
	}
	std::string getJsonStr(){
			  // Create a file stream to write the received file into it.
		  auto fileStream = std::make_shared<ostream>();
		  
		  // Open stream to output file.
		  pplx::task<void> requestTask = fstream::open_ostream(U("users.json"))
		  
		  // Make a GET request.
		  .then([=](ostream outFile) {
		    *fileStream = outFile;// 
		    // https://api.unibit.ai/v2/company/coreFinancials?tickers=ticker list&interval=A, Q or TTM&statement=see possible options&startDate=YYYY-MM-DD&endDate=YYYY-MM-DD&selectedFields=field list&dataType=json or csv&accessKey=your ke
		 
		    // Create http_client to send the request.
		    http_client client(U("https://api.unibit.ai"));
		 // https://api.unibit.ai/v2/stock/historical?tickers=AAPL&interval=1&startDate=2020-01-01&endDate=2020-05-01&dataType=json&accessKey=
		    //https://api.unibit.ai/v2/stock/historical?tickers=AAPL&interval=1&startDate=2020-01-01&endDate=2020-05-01&dataType=json&accessKey=1uQEaW_HL4hT4eDiAOUv9U-1D4dGnKjA

		    // Build request URI and start the request.
		    // https://reqres.in/api/users/1
		    // https://api.unibit.ai/api/realtimestock/AAPL?size=10&AccessKey=demo

		    std::string mess = uri_builder(U("v2")).append_path(U("stock")).append_path(U("historical"))
		      .append_query(U("tickers"), U(ticker))// https://www.drdobbs.com/cloud/using-the-microsoft-c-rest-sdk/240164544?pgno=2
		      .append_query(U("interval"), U("1")) 
		      .append_query(U("startDate"), U("2020-01-01")) 
		      .append_query(U("endDate"), U("2020-01-31")) 
		      .append_query(U("dataType"), U("json")) 
		      .append_query(U("accessKey"), U("x_sIM5r_u20hDiUut_5rwSCmAH9ICDDM"))
		      // RsjvEpx--EWhP77HxToylcMkCPxtF6UA	yezhengli9@outlook.com
		      // 1uQEaW_HL4hT4eDiAOUv9U-1D4dGnKjA	yezhenglimr9@gmail.com
		      // JApS-XgN6FCqejbOq9X3dSBFiHj83-FM	yezheng@sas.upenn.edu
		      // fprsJwbgPXugCTPAfubyqpbJL6EDIXt4	yezheng@seas.upenn.edu
		      // Of-R-Z6k3M_yx1RcgnxJZunhulF63iBU	yezhengintern@gmail.com
		      // wmyObJNSU-l_8b-myUju6Pqhoh08gmjo	mr9@yezhengli@gmail.com
		      // 5RImLiZmCVu0r4HJdeL9IyBGqOyGBEiI	applyyezhengli@gmail.com
		      // u_tBtkk8ORcMQAgzk5KcGnfR5bxRhT4o	yezhengliapplyg@gmail.com
		      // NcMWpvwcgftvWffNyP4P-QeBk-6WG_y8 yezhengdsintern@gmail.com
		      // RvYyGxk3ycXurLljmc9FFeGz9I7dA4fs	yezhengli9sde2@gmail.com
		      // ATQiS0HeYWALwCjWl9M1GbXGxOmqlYdg	yezhenglimr9apply@gmail.com
		      // C_o_eN7FP4zQDKQW1P9PwgmOKA50Jid0	yezhengmr9sde@gmail.com
		      // x_sIM5r_u20hDiUut_5rwSCmAH9ICDDM	yezhengsde@gmail.com
		      .to_string();
		    std::cout<<"message\t" <<mess<< '\n';
		    return client.request(methods::GET, mess);
		  })
		 
		  // Get the response.
		  .then([=](http_response response) {
		    // Check the status code.
		    if (response.status_code() != 200) {
		      throw std::runtime_error("Returned " + std::to_string(response.status_code()));
		    }
		 
		    // // Write the response body to file stream.
		    // response.body().read_to_end(fileStream->streambuf()).wait();// yezheng: this is the original one


		      ///
		// https://www.drdobbs.com/cloud/using-the-microsoft-c-rest-sdk/240164544?pgno=2
		  // Display the status code that the server returned
		        std::wostringstream stream;
		      auto bodyStream = response.body();
		        concurrency::streams::stringstreambuf sbuffer;//streams::stringstreambuf sbuffer; // error: ‘streams’ has not been declared

		      
		 
		        bodyStream.read_to_end(sbuffer).get();
		        // std::cout<< "=====sbuffer\t"<< sbuffer<<"\t\n";
		        stream.str(std::wstring());
		        jsonStr = sbuffer.collection();
		        // std::cout<<"=========jsonStr.c_str()\t"<<jsonStr.c_str()<<"\r\n";
		        // stream << L"Response body: " << jsonStr.c_str();
		        // std::wcout << stream.str(); // std::wcout << stream.str();
		        // jsonStr = target.c_str();
		 
		    // Close the file.
		    return fileStream->close();


		  
		  });
		 
		  // Wait for the concurrent tasks to finish.
		  try {
		    while (!requestTask.is_done()) { 
		    //  std::cout << ".";  //yezheng: comment out!!!
		    }
		  } catch (const std::exception &e) {
		    printf("Error exception:%s\n", e.what());
		  }

		  return jsonStr;
	}

};
#endif