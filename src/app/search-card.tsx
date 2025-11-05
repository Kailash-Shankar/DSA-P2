"use client"

import type React from "react"

import { useState } from "react"
import { SearchIcon } from "lucide-react"

interface SearchCardProps {
  onSearch: (zipCode: string) => void
  loading: boolean
  treeType: "red-black" | "b-tree"
}
const Button: React.FC<React.ButtonHTMLAttributes<HTMLButtonElement>> = ({
  className = "",
  ...props
}) => <button {...props} className={`px-3 py-2 rounded ${className}`} />;

export default function SearchCard({ onSearch, loading, treeType }: SearchCardProps) {
  const [input, setInput] = useState("")
  const [inputError, setInputError] = useState("")

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault()
    setInputError("")

    // Validate zip code format
    if (!input.trim()) {
      setInputError("Please enter a zip code")
      return
    }

    if (!/^\d{5}$/.test(input.trim())) {
      setInputError("Please enter a valid 5-digit zip code")
      return
    }

    onSearch(input.trim())
  }

  return (
    <div className="bg-white rounded-lg border border-slate-200 shadow-sm p-8">
      <div className="mb-6 flex items-center justify-between">
        <h2 className="text-2xl font-bold text-slate-900">Search Properties</h2>
        <span
        className={ `text-xs font-semibold px-3 py-1 rounded-full
    ${treeType === "red-black"
      ? "text-red-600 bg-red-100"
      : "text-green-600 bg-green-100"
    }`}
    >
{treeType === "red-black" ? "Red-Black Tree" : "B-Tree"}
        </span>
      </div>

      <form onSubmit={handleSubmit} className="space-y-4">
        <div>
          <label htmlFor="zipcode" className="block text-sm font-medium text-slate-700 mb-2">
            Zip Code
          </label>
          <div className="relative">
            <input
              id="zipcode"
              type="text"
              inputMode="numeric"
              maxLength={5}
              placeholder="e.g., 10001"
              value={input}
              onChange={(e) => {
                setInput(e.target.value.replace(/\D/g, ""))
                setInputError("")
              }}
              disabled={loading}
              className="w-full px-4 py-3 border border-slate-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-transparent disabled:bg-slate-50 disabled:text-slate-500 transition-colors"
            />
            <SearchIcon className="absolute right-3 top-3 h-5 w-5 text-slate-400" />
          </div>
          {inputError && <p className="text-red-600 text-sm mt-2 font-medium">{inputError}</p>}
        </div>

        <Button
          type="submit"
          disabled={loading}
          className="w-full bg-blue-600 hover:bg-blue-700 text-white font-semibold py-3 rounded-lg transition-colors"
        >
          {loading ? (
            <span className="flex items-center justify-center">
              <svg
                className="animate-spin h-5 w-5 mr-2"
                xmlns="http://www.w3.org/2000/svg"
                fill="none"
                viewBox="0 0 24 24"
              >
                <circle className="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" strokeWidth="4"></circle>
                <path
                  className="opacity-75"
                  fill="currentColor"
                  d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"
                ></path>
              </svg>
              Searching...
            </span>
          ) : (
            "Search"
          )}
        </Button>
      </form>

     
      
    </div>
  )
}
