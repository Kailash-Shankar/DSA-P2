"use client"

import { useState } from "react"
import SearchCard from "./search-card"
import ResultsCard from "./results-card"
import Image from "next/image"
import house from "./house.png"

export default function Home() {
  const [zipCode, setZipCode] = useState("")
  const [results, setResults] = useState(null)
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState("")
  const [treeType, setTreeType] = useState<"red-black" | "b-tree">("red-black")

  const handleSearch = async (code: string) => {
    setZipCode(code)
    setLoading(true)
    setError("")
    setResults(null)


    try{
      console.log("Fetching from backend:", `http://localhost:8080/node/${code}`)

      const response = await fetch(`http://localhost:8080/node/${code}?tree=${treeType}`)

      console.log("Response status:", response.status)

      if (!response.ok){
        throw new Error('No data found for zip ${code}')

      }

      const data = await response.json()
    console.log("Received data:", data)

    setResults({
      state: data.info[0],
      city: data.info[1],
      metro: data.info[2],
      county: data.info[3],
      avgPrice: parseFloat(data.price),
      time: data.time
    }
  )

  }
  catch (err) {
    
    setError(err instanceof Error ? err.message : `No data found for zip code: ${code}`)
    setResults(null)
  } finally {
    setLoading(false)
  }
}

  return (
    <main className="min-h-screen bg-gradient-to-b from-blue-50 to-white">
      <div className="px-[100px] py-12">
        {/* Header */}
        <div className="mb-12">
          <div className="flex items-center justify-center mb-6">
          <Image src={house} alt="House" width={120} height={120} className="rounded-lg" />
          <h1 className="text-5xl font-bold text-slate-900 mb-4 text-center">Home Price Estimator</h1>
          </div>
          <p className="text-xl text-slate-600 text-center">
            Search by zip code to discover average home prices and location details across the US
          </p>
        </div>

        <div className="mb-8">
          <div className="bg-white rounded-lg border border-slate-200 shadow-sm p-4">
            <p className="text-sm font-medium text-slate-700 mb-3">Search Algorithm</p>
            <div className="flex gap-3">
              <button
                onClick={() => setTreeType("red-black")}
                className={`flex-1 px-4 py-2 rounded-lg font-medium transition-colors ${
                  treeType === "red-black" ? "bg-red-600 text-white" : "bg-slate-100 text-slate-700 hover:bg-slate-200"
                }`}
              >
                Red-Black Tree
              </button>
              <button
                onClick={() => setTreeType("b-tree")}
                className={`flex-1 px-4 py-2 rounded-lg font-medium transition-colors ${
                  treeType === "b-tree" ? "bg-green-600 text-white" : "bg-slate-100 text-slate-700 hover:bg-slate-200"
                }`}
              >
                B-Tree
              </button>
            </div>
          </div>
        </div>

        {/* Search and Results - Single Column */}
        <div className="space-y-8">
          <SearchCard onSearch={handleSearch} loading={loading} treeType={treeType} />
          <ResultsCard results={results} loading={loading} error={error} zipCode={zipCode} />
        </div>
      </div>
    </main>
  )
}
